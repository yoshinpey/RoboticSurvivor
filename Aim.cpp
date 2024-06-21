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

    const int halfScreenWidth = Direct3D::screenWidth_ / 2;
    const int halfScreenHeight = Direct3D::screenHeight_ / 2;

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
    
    //マウス初期位置(幅/2, 高さ/2)
    Input::SetMousePosition(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2);


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

    // カメラシェイクを適用
    if (shakeTimeLeft_ > 0)
    {
        camPosFloat3.x += ((rand() % 100) / 100.0f - 0.5f) * shakeMagnitude_ * 2;
        camPosFloat3.y += ((rand() % 100) / 100.0f - 0.5f) * shakeMagnitude_ * 2;
        camPosFloat3.z += ((rand() % 100) / 100.0f - 0.5f) * shakeMagnitude_ * 2;

        shakeTimeLeft_ -= 0.01f;
    }

    eyePositon_ = camPosFloat3;

    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}

// 描画
void Aim::Draw()
{
    // クロスヘアを表示
    pNum_->Draw(halfScreenWidth, halfScreenHeight, "+");
}

// 開放
void Aim::Release()
{
}

void Aim::StartCameraShake(float duration, float magnitude)
{
    shakeDuration_ = duration;
    shakeMagnitude_ = magnitude;
    shakeTimeLeft_ = duration;
}