#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"



//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr),
    gravity_(-0.3), maxFuel_(50), fuel_(0), jumpCool_(0), CanJump_(false), jampVelocity_(1.0),
    maxHp_(100), nowHp_(100)
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
    //Jump();               //ジャンプアクション
    JetPack();              //ジェットパック
    //BoostJump();          //ブーストジャンプ
    CameraPosition();       //視点
    PlayerHitPoint();       //HP
}

//描画
void Player::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //デバック用テキスト
    pNum->Draw(50, 200, "fuel");
    pNum->Draw(50, 250, fuel_);
    pNum->Draw(50, 400, "jumpCool");
    pNum->Draw(50, 450, jumpCool_);

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

//視点
void Player::CameraPosition()
{
#if 0
    //テスト用のカメラ
    XMFLOAT3 camPos{ 0, 10, -20 };
    XMFLOAT3 camTag{ 0, 0, 0 };
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTag);
#endif
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
    if (Input::IsKey(DIK_W)) {
        fMove.x += aimDirection.x;
        fMove.z += aimDirection.z;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x -= aimDirection.z;
        fMove.z += aimDirection.x;
    }
    if (Input::IsKey(DIK_S)) {
        fMove.x -= aimDirection.x;
        fMove.z -= aimDirection.z;
    }
    if (Input::IsKey(DIK_D)) {
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
    bool isMoving = Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D);

    // 移動入力あり
    if (isMoving)
    {
        // 走っているかどうか
        if (Input::IsKey(DIK_LSHIFT))
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
    float gravity = -9.81;               // 
    static bool canJump = true;         // ジャンプ可能な状態かどうか
    static float flightTime = 0.0f;     // ジャンプ経過時間
    bool onGround = transform_.position_.y <= 0;    // 地面にいるとき

    if (Input::IsKeyDown(DIK_SPACE) && canJump) //ジャンプキーが押されており、ジャンプ可能な場合
    {
        flightTime = 0.0f;
        canJump = false;                // 連続ジャンプを防止するため、ジャンプ中はジャンプフラグを無効化
    }

    if (!canJump)
    {
        //ジャンプしてからの時間の経過
        flightTime += delta;
        
        //鉛直投げ上げ運動          y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * flightTime + 0.5f * gravity * flightTime * flightTime;
        transform_.position_.y = pos;

        //重力による落下
        velocity += gravity * delta;

        //地面に着地したとき
        if (onGround)
        {
            transform_.position_.y = 0;     // 念のため地面に合わせる
            canJump = true;                 // 地面に着地したらジャンプ可能にする
        }
    }
}

//ジェットパック
void Player::JetPack()
{
    float flightTime = 0.0f;    // 滞空中の時間経過
    float fallTime = 0.0f;      // 落下時間

    bool onGround = transform_.position_.y <= 0;    // 地面にいるとき
    bool hasFuel = fuel_ > 0;                       // 燃料があるとき

    // 重力は空中にいるときのみ働く
    if(!onGround) transform_.position_.y += gravity_ + fallTime;

    // ジャンプ可能
    if(hasFuel)
    {
        if (Input::IsKey(DIK_SPACE)) // ジャンプキー入力したら
        {
            if (flightTime <= 1) flightTime += 0.1;            //加速限界まで徐々に加速
            transform_.position_.y += jampVelocity_ + flightTime;  //速度にジャンプ時間を加える
            fuel_--;                                            //燃料を減らす
        }
        else
        {
            flightTime = 0; //キー入力がなければ経過時間(加速)をリセット
            fallTime += 0.2;
        }
    }

    // 地面にいるかつ燃料がない
    if (onGround && !hasFuel)
    {
        transform_.position_.y = 0.0f;
        if (jumpCool_ <= 0.0f) jumpCool_ += 20.0f;             // わずかな回復待機時間を設定
    }

    // クールタイムを0まで減らす
    if (jumpCool_ > 0)   jumpCool_--;

    // 燃料は地面にいてクールタイム中でないときに回復
    if (onGround && jumpCool_ <= 0)
    {
        if (fuel_ < maxFuel_) fuel_++; // 燃料を最大値まで回復
    }
}

//組み合わせ
void Player::BoostJump()
{
}
