#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "InputManager.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"


//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr),
    gravity_(-9.8), CanJump_(false), maxHp_(100), nowHp_(100)
{
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
    Move();                 //動き
    Jump();                 //ジャンプアクション
    PlayerHitPoint();       //HP
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

//プレイヤーの移動
void Player::Move()
{
    // 移動
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

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

    // 正規化する
    float moveLength = sqrtf(fMove.x * fMove.x + fMove.z * fMove.z);
    if (moveLength != 0)
    {
        fMove.x /= moveLength;
        fMove.z /= moveLength;
    }

    // 速度の制御
    float walkSpeed = 0.2f;         // 歩行速度
    float runSpeed = 0.3f;          // 走行速度
    float nowSpeed = 0;             // 初期速度

    // 移動入力があるかどうか
    bool isMoving = InputManager::IsMoveForward() || InputManager::IsMoveLeft() || InputManager::IsMoveBackward() || InputManager::IsMoveRight();

    // 移動入力あり
    if (isMoving)
    {
        // 走っているかどうか
        if (InputManager::IsRun())
        {
            nowSpeed = runSpeed;    // 走り速度を設定
        }
        else
        {
            nowSpeed = walkSpeed;   // 歩き速度を設定
        }
    }
    else
    {
        // 各移動ボタンを離したときに速度をリセット
        nowSpeed = 0.0f;
    }

    // 移動に反映
    transform_.position_.x += fMove.x * nowSpeed;
    transform_.position_.z += fMove.z * nowSpeed;
}

//通常ジャンプ
void Player::Jump()
{
    float velocity = 5.0f;              // 初速度
    float delta = 0.02f;                // 適当なごく小さい値
    static bool canJump = true;         // ジャンプ可能な状態かどうか
    static float flightTime = 0.0f;     // ジャンプ経過時間

    if (InputManager::IsJump() && canJump) //ジャンプキーが押されており、ジャンプ可能な場合
    {
        flightTime = 0.0f;
        canJump = false;                // 連続ジャンプを防止するため、ジャンプ中はジャンプフラグを無効化
    }

    if (!canJump)
    {
        //ジャンプしてからの時間の経過
        flightTime += delta;
        
        //鉛直投げ上げ運動          y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * flightTime + 0.5f * gravity_ * flightTime * flightTime;
        transform_.position_.y = pos;

        //重力による落下
        velocity += gravity_ * delta;

        //地面に着地したとき
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;     // 地面に合わせる
            canJump = true;                 // 地面に着地したらジャンプ可能にする
        }
    }
}