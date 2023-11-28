#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "Aim.h"
#include "Player.h"
#include "Gauge.h"


//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr),
    gravity_(-1), canJump_(true), maxHp_(100), nowHp_(100), jumpVelocity_(JUMP_HEIGHT), jumpDelta_(0.08f), velocity_(0.0f, 0.0f, 0.0f),
    walkSpeed_(WALK_SPEED), runSpeed_(RUN_SPEED), isMoving_(false), movement_(0.0f, 0.0f, 0.0f), acceleration_(0.01f), friction_(0.8f)
{
    // プレイヤー固有のステータスを設定
    characterStatus_.SetStatus(/* プレイヤーステータスのパラメータ */);
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Character/Human_only.fbx");
    assert(hModel_ >= 0);

    //視点クラス読み込み
    Instantiate<Aim>(this);

    //テキスト
    pNum = new Text;
    pNum->Initialize();
}

//更新
void Player::Update()
{

    /////////修正予定
    Move();                 //動き
    Jump();                 //ジャンプアクション
    PlayerHitPoint();       //HP
    /////////
}

//描画
void Player::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //デバック用テキスト
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
}

//プレイヤーのHP
void Player::PlayerHitPoint()
{
    //HPゲージ呼び出し
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(maxHp_, nowHp_);

    //エラー潰し
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

// プレイヤーの移動
void Player::Move()
{
    // 移動方向
    XMFLOAT3 fMove = CalculateMoveInput();

    // 移動入力があるときは真
    isMoving_ = InputManager::IsMoveForward() || InputManager::IsMoveLeft() || InputManager::IsMoveBackward() || InputManager::IsMoveRight();

    // 現在の速度
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&movement_)));

    // 最高速度
    float maxMoveSpeed = 0.0f;

    // 移動入力あり
    if (isMoving_)
    {
        // 走っているかどうか
        if (InputManager::IsRun())
        {
            maxMoveSpeed = runSpeed_;    // 走り速度に設定
        }
        else
        {
            maxMoveSpeed = walkSpeed_;   // 歩き速度に設定
        }

        // 最大速度を超えていたら正規化・最大値の値にする
        if (currentSpeed > maxMoveSpeed)
        {
            XMVECTOR vMove = XMLoadFloat3(&movement_);
            vMove = XMVector3Normalize(vMove);
            vMove *= maxMoveSpeed;
            XMStoreFloat3(&movement_, vMove);
        }

        // 現在の速度を目標の速度に近づける
        if (currentSpeed < maxMoveSpeed)
        {
            velocity_.x += acceleration_;
            velocity_.z += acceleration_;
        }
        else
        {
            velocity_.x = maxMoveSpeed;
            velocity_.z = maxMoveSpeed;
        }

        // 移動に反映
        movement_.x += fMove.x * velocity_.x;
        movement_.z += fMove.z * velocity_.z;

        // 移動量を適用
        transform_.position_.x += movement_.x;
        transform_.position_.z += movement_.z;
    }
    else
    {
        // 各移動ボタンを離したときに減速を適応
        movement_.x *= friction_;
        movement_.z *= friction_;
        velocity_.x = 0;
        velocity_.z = 0;

        // 移動に反映
        transform_.position_.x += movement_.x;
        transform_.position_.z += movement_.z;
    }
}

// ジャンプ
void Player::Jump()
{
    // ジャンプキーが押されており、ジャンプ可能な場合
    if (InputManager::IsJump() && canJump_)
    {
        // ジャンプ開始時に初速度を与える
        velocity_.y = jumpVelocity_;

        // 連続ジャンプを防止
        canJump_ = false;
    }

    // 滞空中
    if (!canJump_)
    {
        // 上方向への移動加速
        transform_.position_.y += velocity_.y * jumpDelta_;

        // 重力を適用してジャンプの高さを制御
        velocity_.y += gravity_ * jumpDelta_;

        // 地面に着地したとき
        if (transform_.position_.y <= 0)
        {
            // 地面に合わせる
            transform_.position_.y = 0;

            // 着地したら垂直速度をリセット
            velocity_.y = 0.0f;

            // 地面に着地したらジャンプ可能にする
            canJump_ = true;
        }
    }
}

// 移動計算を行う関数
XMFLOAT3 Player::CalculateMoveInput()
{
    XMFLOAT3 fMove = XMFLOAT3(0.0f, 0.0f, 0.0f);

    // エイム情報呼び出し
    Aim* pAim = (Aim*)FindObject("Aim");
    XMFLOAT3 aimDirection = pAim->GetAimDirection();

    // PlayerクラスのMove関数内の一部
    if (InputManager::IsMoveForward())
    {
        fMove.x += aimDirection.x;
        fMove.z += aimDirection.z;
    }
    if (InputManager::IsMoveLeft())
    {
        fMove.x -= aimDirection.z;
        fMove.z += aimDirection.x;
    }
    if (InputManager::IsMoveBackward())
    {
        fMove.x -= aimDirection.x;
        fMove.z -= aimDirection.z;
    }
    if (InputManager::IsMoveRight())
    {
        fMove.x += aimDirection.z;
        fMove.z -= aimDirection.x;
    }

    // 正規化
    XMVECTOR vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    XMStoreFloat3(&fMove, vMove);

    return fMove;
}
