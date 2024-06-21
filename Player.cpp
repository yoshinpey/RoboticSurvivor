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
    : Character(parent, "Player"), pStateManager_(nullptr), pAim_(nullptr), pGauge_(nullptr), knockDirection_(0.0f, 0.0f, 0.0f), isEnemyHit_(false)
{
    // 標準パラメータをセット
    commonParameter_.walkSpeed_ = GetPrivateProfileFloat("Parameter", "walkSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.runSpeed_ = GetPrivateProfileFloat("Parameter", "runSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.jumpVelocity_ = GetPrivateProfileFloat("Parameter", "jumpHeight", 0, "Settings/PlayerSettings.ini");
    commonParameter_.knockBackStrength_ = 0.1f;

    // ステータスをセット
    commonStatus_.maxHp_ = GetPrivateProfileFloat("Status", "maxHp", 0, "Settings/PlayerSettings.ini");

    // ステートマネージャー設定
    pStateManager_ = new StateManager(this);
    pStateManager_->AddState("IdleState", new PlayerIdleState(pStateManager_));
    pStateManager_->AddState("WalkingState", new PlayerWalkingState(pStateManager_));
    pStateManager_->AddState("RunningState", new PlayerRunningState(pStateManager_));
    pStateManager_->AddState("JumpingState", new PlayerJumpingState(pStateManager_));
    pStateManager_->ChangeState("IdleState");           // 初期状態

    // 当たり判定付与
    SphereCollider* pCollision = new SphereCollider(collisionOffset, collisionScale);
    AddCollider(pCollision);
}

// デストラクタ
Player::~Player()
{
    SAFE_DELETE(pStateManager_);

    // 死んだときにプレイヤーのポインターを解放する
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

    // 重力加算
    ApplyGravity();
    
    // 敵と衝突
    if (isEnemyHit_)
    {
        playerParams_.jumping_ = true;
        //// 減衰値の調整でノックバックの威力を変更している。////
        // ノックバック減衰
        knockDirection_.x -= knockDirection_.x * commonParameter_.knockBackStrength_;
        knockDirection_.z -= knockDirection_.z * commonParameter_.knockBackStrength_;

        // Y軸のノックバック減衰と重力適用
        knockDirection_.y -= knockDirection_.y * (commonParameter_.knockBackStrength_ * 3.0f);

        transform_.position_.x += knockDirection_.x;
        transform_.position_.y += knockDirection_.y;
        transform_.position_.z += knockDirection_.z;

        // ノックバックがほとんどなくなったらフラグをリセット
        if (fabs(knockDirection_.x) < 0.01f && fabs(knockDirection_.z) < 0.01 && fabs(knockDirection_.y) < 0.01f)
        {
            isEnemyHit_ = false;
        }
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
        vMove = XMVector3Normalize(vMove) * speed;
        XMStoreFloat3(&playerParams_.movement_, vMove);
    }

    // 移動に反映
    playerParams_.movement_.x += moveVector.x * playerParams_.acceleration_;
    playerParams_.movement_.z += moveVector.z * playerParams_.acceleration_;

    // 移動量を適用
    transform_.position_.x += playerParams_.movement_.x;
    transform_.position_.z += playerParams_.movement_.z;
}

// 移動の減速を適用する関数
void Player::ApplyDeceleration()
{
    // 減速係数を適応する
    if (playerParams_.jumping_)
    {
        // 滞空中の減速係数
        playerParams_.movement_.x *= playerParams_.friction_ * playerParams_.jumpFriction_;
        playerParams_.movement_.z *= playerParams_.friction_ * playerParams_.jumpFriction_;
    }
    else
    {
        // 地面にいるときの減速係数
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

    // 逆キー入力したら移動変数の逆行列を掛けてストップさせる
    if (InputManager::IsMoveForward() && InputManager::IsMoveBackward() && !InputManager::IsMoveLeft() && !InputManager::IsMoveRight()) 
        return XMFLOAT3(-playerParams_.movement_.x, -playerParams_.movement_.y, -playerParams_.movement_.z);
    else if (InputManager::IsMoveLeft() && InputManager::IsMoveRight() && !InputManager::IsMoveForward() && !InputManager::IsMoveBackward()) 
        return XMFLOAT3(-playerParams_.movement_.x, -playerParams_.movement_.y, -playerParams_.movement_.z);
    else if (InputManager::IsMoveForward() && InputManager::IsMoveBackward() && !InputManager::IsMoveLeft() && !InputManager::IsMoveRight()) 
        return XMFLOAT3(-playerParams_.movement_.x, -playerParams_.movement_.y, -playerParams_.movement_.z);


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


    //if (Input::IsKey(DIK_SPACE))transform_.position_.y += 0.6;
        
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
        // エネミーベースにキャスト
        EnemyBase* pEnemy = dynamic_cast<EnemyBase*>(pTarget);

        // HP減らす処理
        //if (!isEnemyHit_)DecreaseHp(pEnemy->GetEnemyStatus().attackPower_);
        // カメラシェイクをトリガー
        pAim_->StartCameraShake(0.3f, 0.05f); // 強さ0.2, 0.5秒間のシェイク

        // 敵にぶつかったらノックバック値を設定する
        // ノックバック関数に自身の座標と敵の座標、ノックバックさせる威力を渡す
        // 受け取った座標の引き算をして、正規化を行い方向を求める。
        // 方向に威力をかけてノックバックベクトルを作成する

        // アップデート関数で現在地ベクトルにノックバックベクトルをかけてやりノックバックさせる。
        // しかしこのままではいつまでも止まらないので、ノックバックの減衰を行う。
        // ノックバックベクトルが0より大きくなったら、ノックバックベクトルに減衰変数をかける。
        // 減衰値が大きいほど結果的にノックバックの威力が下がる(ノックバックベクトルが0に達するまでの時間が減るため)
        // Y軸に関してはぶつかり角度を考慮せず上に飛ばしたいので、1.0を与え、それに減衰値のn倍かけてやる。
        // ノックバックベクトルが0になる、かつ地面に足がついたらノックバック計算を終了する。


        // エネミー位置
        XMFLOAT3 enemyPos = pEnemy->GetPosition();

        // プレイヤーからエネミーへの方向(ノックバックの方向)ベクトルを計算
        knockDirection_ = CalculateDirection(transform_.position_, enemyPos);
        knockDirection_.y = 1.0f;   // 0だと上に飛ばないので1にする
        isEnemyHit_ = true;
    }
}
