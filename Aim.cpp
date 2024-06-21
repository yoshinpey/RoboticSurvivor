#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Player.h"
#include "Aim.h"
#include "Gun.h"
#include <algorithm>

namespace
{
    const float upLimit = 89.0f;
    const float downLimit = -89.0f;

    XMFLOAT3 FORWARD_VECTOR = { 0.0f,0.0f,1.0f };
}

// コンストラクタ
Aim::Aim(GameObject* parent) : GameObject(parent, "Aim"), pNum_(nullptr), pPlayer_(nullptr),
aimDirection_{ 0,0,0 }, camPos_{0,0,0}, mouseSensitivity_{0, 0}, eyePositon_{0,0,0}
{
    // マウス感度をINIファイルから取得
    mouseSensitivity_.x = GetPrivateProfileFloat("MOUSE_SENSITIVITY", "X", 0, "./setup.ini");
    mouseSensitivity_.y = GetPrivateProfileFloat("MOUSE_SENSITIVITY", "Y", 0, "./setup.ini");
}

// デストラクタ
Aim::~Aim()
{
}

// 初期化
void Aim::Initialize()
{
    // エイムクラスの呼び出し位置
    transform_.position_.y = EYE_POSITION;

    // マウス座標ポインター
    pNum_ = new Text;
    pNum_->Initialize();

    // 銃はカメラにくっつく
    Instantiate<Gun>(this);

    // プレイヤーオブジェクト取得
    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

// 更新
void Aim::Update()
{ 
    UpdateRotation();
    UpdateCameraPosition();
}

void Aim::UpdateRotation()
{
    // 水平方向の回転を更新
    transform_.rotate_.y += Input::GetMouseMove().x * mouseSensitivity_.x;

    // 垂直方向の回転は上下の限界を超えないように制限
    float newRotationX = transform_.rotate_.x + Input::GetMouseMove().y * mouseSensitivity_.y;
    transform_.rotate_.x = std::clamp(newRotationX, downLimit, upLimit);
}

void Aim::UpdateCameraPosition()
{
    // カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mView = mRotX * mRotY;

    // カメラ位置の計算
    XMFLOAT3 plaPos = pPlayer_->GetPosition();
    camPos_ = { plaPos.x , plaPos.y + EYE_POSITION, plaPos.z };

    // カメラの位置と焦点を取得
    XMVECTOR camPosVector = XMLoadFloat3(&camPos_);
    XMVECTOR forwardVector = XMVector3TransformCoord(XMLoadFloat3(&FORWARD_VECTOR), mView);

    ///////////////プレイヤークラスに見ている方向を伝える
    XMStoreFloat3(&aimDirection_, forwardVector);
    ////////////////////////////////////////////////////
    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    // カメラの位置と焦点を設定
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);

    // フレームごとの時間経過を利用してカメラの揺れを制御する
    static float timeElapsed = 0.0f;
    float deltaTime = 1.0f / 60.0f; // 60FPS を前提として、1フレームの時間を設定

    // カメラシェイクを適用
    if (shakeTimeLeft_ > 0)
    {
        float shakeAmount = sin(timeElapsed * XM_PI * 10.0f) * shakeMagnitude_; // 10.0f は揺れの周波数を調整するパラメータ
        camPosFloat3.x += shakeAmount;
        camPosFloat3.y += shakeAmount;
        camPosFloat3.z += shakeAmount;

        shakeTimeLeft_ -= deltaTime;
        timeElapsed += 0.01;
    }
    else
    {
        timeElapsed = 0.0f; // シェイクが終了したら時間をリセット
    }

    eyePositon_ = camPosFloat3;

    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}

// 描画
void Aim::Draw()
{
    // クロスヘアを表示
    pNum_->Draw(Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2, "+");
}

// 開放
void Aim::Release()
{
}

void Aim::StartCameraShake(float time, float strength)
{
    shakeTimeLeft_ = time;
    shakeMagnitude_ = strength;
}