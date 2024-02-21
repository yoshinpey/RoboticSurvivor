#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Text.h"

#include "StateManager.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"
#include "Ground.h"
#include "PlayerState.h"

//コンストラクタ
Player::Player(GameObject* parent) : PlayerBase(parent, "Player"),
    pText_(nullptr), pStateManager_(nullptr), pAim_(nullptr),
    gravity_(-1), jumping_(false), nowHp_(0), jumpDelta_(0.01f), velocity_(0.0f, 0.0f, 0.0f),
    movement_(0.0f, 0.0f, 0.0f), acceleration_(0.03f), friction_(0.85f), jumpFriction_(1.15f)
{
    // パラメータをセット
    parameter_.walkSpeed_       = GetPrivateProfileFloat("Parameter", "walkSpeed", 0, "Settings/PlayerSettings.ini");
    parameter_.runSpeed_        = GetPrivateProfileFloat("Parameter", "runSpeed", 0, "Settings/PlayerSettings.ini");
    parameter_.jumpVelocity_    = GetPrivateProfileFloat("Parameter", "jumpHeight", 0, "Settings/PlayerSettings.ini");

    // ステータスをセット
    status_.maxHp_              = GetPrivateProfileFloat("Status", "maxHp", 0, "Settings/PlayerSettings.ini");
    nowHp_ = status_.maxHp_;    // 現在のHPを最大値で初期化

    // ステートマネージャー
    pStateManager_ = new StateManager(this);

    //テキスト
    pText_ = new Text;

}

//デストラクタ
Player::~Player()
{
    SAFE_DELETE(pStateManager_);
}

//初期化
void Player::Initialize()
{
    pText_->Initialize();

    //視点クラス読み込み
    InstantiateFront<Aim>(this);
    pAim_ = (Aim*)FindObject("Aim");

    //ステージオブジェクトを探す
    //Ground* pGround = (Ground*)FindObject("Ground");
    //hGroundModel_ = pGround->GetModelHandle();

    // あらかじめ状態インスタンスを生成して登録
    pStateManager_->AddState("IdleState", new PlayerIdleState(pStateManager_));
    pStateManager_->AddState("WalkingState", new PlayerWalkingState(pStateManager_));
    pStateManager_->AddState("RunningState", new PlayerRunningState(pStateManager_));
    pStateManager_->AddState("JumpingState", new PlayerJumpingState(pStateManager_));

    // 初期状態
    pStateManager_->ChangeState("IdleState");
}

//更新
void Player::Update()
{
    // ステートマネージャーの更新
    pStateManager_->Update();

    if (jumping_)
    {
        ApplyGravity();
    }
}

//描画
void Player::Draw()
{
    //デバック用
    pText_->Draw(1150, 100, "X:");
    pText_->Draw(1200, 100, (int)transform_.position_.x);
    pText_->Draw(1150, 250, "Y:");
    pText_->Draw(1200, 250, (int)transform_.position_.y);
    pText_->Draw(1150, 400, "Z:");
    pText_->Draw(1200, 400, (int)transform_.position_.z);
}

//開放
void Player::Release()
{
    SAFE_DELETE(pText_);
}

//プレイヤーのHP
void Player::PlayerHitPoint()
{
    //////////////////UIマネージャー経由に変更予定。
    //HPゲージ呼び出し
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(status_.maxHp_, nowHp_);

    //デバッグ用
    if (Input::IsKeyDown(DIK_M))
    {
        nowHp_ += 20.0f;
        if (nowHp_ > status_.maxHp_)
        {
            nowHp_ = status_.maxHp_;
        }
    }
    if (Input::IsKeyDown(DIK_N))
    {
        nowHp_ -= 20.0f;
        if (nowHp_ < 0.0f)
        {
            nowHp_ = 0.0f;
        }
    }
}

void Player::Walk()
{
    ApplyMovement(CalculateMoveInput(), parameter_.walkSpeed_);
}

void Player::Run()
{
    ApplyMovement(CalculateMoveInput(), parameter_.runSpeed_);
}

// 移動に反映する関数
void Player::ApplyMovement(const XMFLOAT3& moveVector, float speed)
{
    // 現在の速度
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&movement_)));

    // 最大速度を超えていたら正規化、最大値の値にする
    if (currentSpeed > speed)
    {
        XMVECTOR vMove = XMLoadFloat3(&movement_);
        vMove = XMVector3Normalize(vMove);
        vMove *= speed;
        XMStoreFloat3(&movement_, vMove);
    }

    // 移動に反映
    movement_.x += moveVector.x * acceleration_;
    movement_.z += moveVector.z * acceleration_;


    // 移動量を適用
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;

}

// 減速を適用する関数
void Player::ApplyDeceleration()
{
    // 滞空中は減速係数を変える
    if (jumping_)
    {
        movement_.x *= friction_ * jumpFriction_;
        movement_.z *= friction_ * jumpFriction_;
    }
    else
    {
        movement_.x *= friction_;
        movement_.z *= friction_;
    }

    // 移動に反映
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;
}

// ジャンプ
void Player::Jump()
{
    if (jumping_) return;

    // 移動方向を取得
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // 移動方向をジャンプの方向として適用
    velocity_.x = parameter_.jumpVelocity_ * moveDirection.x;
    velocity_.y = parameter_.jumpVelocity_;
    velocity_.z = parameter_.jumpVelocity_ * moveDirection.z;

    //デバック用
    OutputDebugStringA(std::to_string(parameter_.jumpVelocity_).c_str());
    OutputDebugString("\n");

    // ジャンプできなくする
    jumping_ = true;
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

void Player::ApplyGravity()
{
    velocity_.y += gravity_ * jumpDelta_;
    transform_.position_.y += velocity_.y;

    // 地面に到達したらジャンプ可能な状態に戻す
    if (transform_.position_.y <= 0)
    {
        transform_.position_.y = 0;
        jumping_ = false;
        velocity_.y = 0;
    }
}

//bool Player::RayCastStage(XMFLOAT3 position)
//{
//    if (!useRayCast_) return false;
//
//    RayCastData data;
//    data.start = position;                  // レイの発射座標
//    data.start.y = 0;                       // レイの発射位置
//    data.dir = { 0, -1, 0 };                // レイの方向
//    Model::RayCast(hGroundModel_, &data);
//
//    // 当たったら、距離分位置を下げる
//    if (data.hit) 
//    { 
//        transform_.position_.y = -data.dist; 
//        return true;
//    }
//    return false;
//}