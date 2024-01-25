#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "Aim.h"
#include "Player.h"
#include "Gauge.h"

//コンストラクタ
Player::Player(GameObject* parent) : CharacterBase(parent, "Player"),
    pNum(nullptr), stateManager_(nullptr), pAim_(nullptr),
    gravity_(-1), canJump_(true), maxHp_(100), nowHp_(100), jumpVelocity_(JUMP_HEIGHT), jumpDelta_(0.01f), velocity_(0.0f, 0.0f, 0.0f),
    walkSpeed_(WALK_SPEED), runSpeed_(RUN_SPEED), movement_(0.0f, 0.0f, 0.0f), acceleration_(0.01f), friction_(0.85f), jumpFriction_(1.15f),
    jumpDirection_(0.0f, 0.0f, 0.0f), jumpSpeed_(0.0f, 0.0f, 0.0f)
{
    // プレイヤーのステータスを設定
    pCharacterBase_ = static_cast<Player*>(this);
    pCharacterBase_->SetCharacterStatus(maxHp_, nowHp_);
    pCharacterBase_->SetMovementParameters(jumpVelocity_, walkSpeed_, runSpeed_);
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    // ステートマネージャーの初期化
    stateManager_ = new StateManager(this);
    stateManager_ -> Initialize();

    //テキスト
    pNum = new Text;
    pNum->Initialize();

    //視点クラス読み込み
    InstantiateFront<Aim>(this);
    pAim_ = (Aim*)FindObject("Aim");
}

//更新
void Player::Update()
{
    // ステートマネージャーの更新
    stateManager_->Update();

    // 落下処理
    if (!canJump_)
    {
        velocity_.y += gravity_ * jumpDelta_;
        transform_.position_.y += velocity_.y;

        // 地面に到達したらジャンプ可能な状態に戻す
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;
            canJump_ = true;

            velocity_.y = 0;
        }
    }
}

//描画
void Player::Draw()
{

    //デバック用
    pNum->Draw(1150, 100, "X:");
    pNum->Draw(1200, 100, (int)transform_.position_.x);
    pNum->Draw(1150, 250, "Y:");
    pNum->Draw(1200, 250, (int)transform_.position_.y);
    pNum->Draw(1150, 400, "Z:");
    pNum->Draw(1200, 400, (int)transform_.position_.z);
}

//開放
void Player::Release()
{
    SAFE_DELETE(pNum);
}

//プレイヤーのHP
void Player::PlayerHitPoint()
{
    //////////////////UIマネージャー経由に変更予定。
    //HPゲージ呼び出し
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(maxHp_, nowHp_);

    //デバッグ用
    if (Input::IsKeyDown(DIK_M))
    {
        nowHp_ += 20;
        if (nowHp_ > maxHp_)
        {
            nowHp_ = maxHp_;
        }
    }
    if (Input::IsKeyDown(DIK_N))
    {
        nowHp_ -= 20;
        if (nowHp_ < 0)
        {
            nowHp_ = 0;
        }
    }
}

void Player::Walk()
{
    // 移動方向
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // 移動ベクトル
    XMFLOAT3 walkVector = XMFLOAT3(moveDirection.x * walkSpeed_, 0.0f, moveDirection.z * walkSpeed_);

    // 移動に反映
    ApplyMovement(walkVector, walkSpeed_);
}

void Player::Run()
{
    // 移動方向
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // 移動ベクトル
    XMFLOAT3 runVector = XMFLOAT3(moveDirection.x * runSpeed_, 0.0f, moveDirection.z * runSpeed_);

    // 移動に反映
    ApplyMovement(runVector, runSpeed_);
}

// 移動に反映する関数
void Player::ApplyMovement(const XMFLOAT3& moveVector, float speed)
{
    // 現在の速度
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&movement_)));

    // 最大速度を超えていたら正規化・最大値の値にする
    if (currentSpeed > speed)
    {
        XMVECTOR vMove = XMLoadFloat3(&movement_);
        vMove = XMVector3Normalize(vMove);
        vMove *= speed;
        XMStoreFloat3(&movement_, vMove);
    }
    else
    {
        velocity_.x += acceleration_;
        velocity_.z += acceleration_;
    }

    // 移動に反映
    movement_.x += moveVector.x * velocity_.x;
    movement_.z += moveVector.z * velocity_.z;

    // 移動量を適用
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;
}

// 減速を適用する関数
void Player::ApplyDeceleration()
{
    // 各移動ボタンを離したときに減速を適応
    // 滞空中は減速係数を変える
    if (!canJump_)
    {
        movement_.x *= friction_ * jumpFriction_;
        movement_.z *= friction_ * jumpFriction_;
    }
    else
    {
        movement_.x *= friction_;
        movement_.z *= friction_;
    }
    velocity_.x = 0;
    velocity_.z = 0;

    // 移動に反映
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;
}

// ジャンプ
void Player::Jump()
{
    // ジャンプ中は重力を適用しない
    if (!canJump_) return;

    // 移動方向を取得
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // 現在の速度を保持
    XMFLOAT3 currentVelocity = velocity_;

    // 移動方向をジャンプの方向として適用
    velocity_.x = jumpVelocity_ * moveDirection.x;
    velocity_.y = jumpVelocity_;
    velocity_.z = jumpVelocity_ * moveDirection.z;

    // ジャンプ可能な状態を無効にする
    canJump_ = false;

    // 移動方向と速度を保持
    jumpDirection_ = moveDirection;
    jumpSpeed_ = currentVelocity;
}

// 移動計算を行う関数
XMFLOAT3 Player::CalculateMoveInput()
{
    // 計算結果入れる用
    XMFLOAT3 moveDirection = XMFLOAT3(0.0f, 0.0f, 0.0f);

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
    NormalizeFloat3(moveDirection);

    return moveDirection;
}