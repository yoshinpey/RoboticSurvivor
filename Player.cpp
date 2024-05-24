#include "Player.h"
#include "StateManager.h"
#include "Aim.h"
#include "Gauge.h"
#include "PlayerState.h"
#include "EnemyBase.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 1.6f, 0.0f };    // 当たり判定の位置
    float collisionScale = 0.6f;                        // 当たり判定の大きさ
}

// コンストラクタ
Player::Player(GameObject* parent) 
    : PlayerBase(parent, "Player"), pStateManager_(nullptr), pAim_(nullptr), pGauge_(nullptr)
{
    // 標準パラメータをセット
    commonParameter_.walkSpeed_ = GetPrivateProfileFloat("Parameter", "walkSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.runSpeed_ = GetPrivateProfileFloat("Parameter", "runSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.jumpVelocity_ = GetPrivateProfileFloat("Parameter", "jumpHeight", 0, "Settings/PlayerSettings.ini");

    // ステータスをセット
    commonStatus_.maxHp_ = GetPrivateProfileFloat("Status", "maxHp", 0, "Settings/PlayerSettings.ini");

    // ステートマネージャー
    pStateManager_ = new StateManager(this);

    // あらかじめ状態インスタンスを生成して登録
    pStateManager_->AddState("IdleState", new PlayerIdleState(pStateManager_));
    pStateManager_->AddState("WalkingState", new PlayerWalkingState(pStateManager_));
    pStateManager_->AddState("RunningState", new PlayerRunningState(pStateManager_));
    pStateManager_->AddState("JumpingState", new PlayerJumpingState(pStateManager_));

    // 初期状態
    pStateManager_->ChangeState("IdleState");

    // 当たり判定付与
    SphereCollider* pCollision = new SphereCollider(collisionOffset, collisionScale);
    AddCollider(pCollision);
}

// デストラクタ
Player::~Player()
{
    SAFE_DELETE(pStateManager_);

    // 死んだときにポインターをnullにする
    PlayScene* pPlayScene = static_cast<PlayScene*>(FindObject("PlayScene"));
    pPlayScene->SetPlayer(nullptr);
}

// 初期化
void Player::Initialize()
{
    // 視点クラス読み込み
    pAim_ = Instantiate<Aim>(this);
    // HPゲージ
    pGauge_ = Instantiate<Gauge>(this);
}

// 更新
void Player::Update()
{
    // ステートマネージャーの更新
    pStateManager_->Update();

    // HPゲージ呼び出し
    pGauge_->SetHp(commonStatus_.maxHp_, commonStatus_.currentHp_);
    ///////////////////////// デバッグ用
    static float hp = 5.0f;
    if (Input::IsKeyDown(DIK_M))
    {
        IncreaseHp(hp);
    }
    if (Input::IsKeyDown(DIK_N))
    {
        DecreaseHp(hp);
    }
    //////////////////////////

    if (playerParams_.jumping_)
    {
        ApplyGravity();
    }
}

// 描画
void Player::Draw()
{
}

// 開放
void Player::Release()
{
}

void Player::Walk()
{
    ApplyMovement(CalculateMoveInput(), commonParameter_.walkSpeed_);
}

void Player::Run()
{
    ApplyMovement(CalculateMoveInput(), commonParameter_.runSpeed_);
}

// 移動に反映する関数
void Player::ApplyMovement(const XMFLOAT3& moveVector, float speed)
{
    // 現在の速度
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&playerParams_.movement_)));

    // 最大速度を超えていたら正規化、最大値の値にする
    if (currentSpeed > speed)
    {
        XMVECTOR vMove = XMLoadFloat3(&playerParams_.movement_);
        vMove = XMVector3Normalize(vMove);
        vMove *= speed;
        XMStoreFloat3(&playerParams_.movement_, vMove);
    }

    // 移動に反映
    playerParams_.movement_.x += moveVector.x * playerParams_.acceleration_;
    playerParams_.movement_.z += moveVector.z * playerParams_.acceleration_;

    // 移動量を適用
    transform_.position_.x += playerParams_.movement_.x;
    transform_.position_.z += playerParams_.movement_.z;
}

// 減速を適用する関数
void Player::ApplyDeceleration()
{
    // 滞空中は減速係数を変える
    if (playerParams_.jumping_)
    {
        playerParams_.movement_.x *= playerParams_.friction_ * playerParams_.jumpFriction_;
        playerParams_.movement_.z *= playerParams_.friction_ * playerParams_.jumpFriction_;
    }
    else
    {
        playerParams_.movement_.x *= playerParams_.friction_;
        playerParams_.movement_.z *= playerParams_.friction_;
    }

    // 移動に反映
    transform_.position_.x += playerParams_.movement_.x;
    transform_.position_.z += playerParams_.movement_.z;
}

// ジャンプ
void Player::Jump()
{
    if (playerParams_.jumping_) return;

    // 移動方向を取得
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // 移動方向をジャンプの方向として適用
    playerParams_.velocity_.x = commonParameter_.jumpVelocity_ * moveDirection.x;
    playerParams_.velocity_.y = commonParameter_.jumpVelocity_;
    playerParams_.velocity_.z = commonParameter_.jumpVelocity_ * moveDirection.z;

    // ジャンプできなくする
    playerParams_.jumping_ = true;
}

// 移動計算を行う関数
XMFLOAT3 Player::CalculateMoveInput()
{
    // 計算結果入れる用
    XMFLOAT3 moveDirection = { 0.0f, 0.0f, 0.0f };

    // エイム情報呼び出し
    XMFLOAT3 aimDirection = pAim_->GetAimDirection();

    // PlayerクラスのMove関数内の一部
    if (InputManager::IsMoveForward())
    {
        moveDirection.x += aimDirection.x;
        moveDirection.z += aimDirection.z;
    }
    if (InputManager::IsMoveLeft())
    {
        moveDirection.x -= aimDirection.z;
        moveDirection.z += aimDirection.x;
    }
    if (InputManager::IsMoveBackward())
    {
        moveDirection.x -= aimDirection.x;
        moveDirection.z -= aimDirection.z;
    }
    if (InputManager::IsMoveRight())
    {
        moveDirection.x += aimDirection.z;
        moveDirection.z -= aimDirection.x;
    }

    // 正規化
    moveDirection = NormalizeFloat3(moveDirection);

    return moveDirection;
}

void Player::ApplyGravity()
{
    playerParams_.velocity_.y += playerParams_.gravity_ * playerParams_.jumpDelta_;
    transform_.position_.y += playerParams_.velocity_.y;

    // 地面に到達したらジャンプ可能な状態に戻す
    if (transform_.position_.y < 0)
    {
        transform_.position_.y = 0;
        playerParams_.jumping_ = false;
        playerParams_.velocity_.y = 0;
    }
}

// 何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // ノックバック処理
        EnemyBase* pEnemy = dynamic_cast<EnemyBase*>(pTarget);

        // HP減らす処理
        DecreaseHp(pEnemy->GetEnemyStatus().attackPower_);
    }
}
