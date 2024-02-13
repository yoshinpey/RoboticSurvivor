#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Player.h"
#include "Aim.h"
#include "Gun.h"

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
    transform_.rotate_.y += Input::GetMouseMove().x * mouseSensitivity_.x;
    transform_.rotate_.x += Input::GetMouseMove().y * mouseSensitivity_.y;
}

void Aim::UpdateCameraPosition() 
{
    // カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mView = mRotX * mRotY;

    // カメラ位置の計算
    camPos_.x = pPlayer_->GetPosition().x;
    camPos_.y = pPlayer_->GetPosition().y + EYE_POSITION; // 目線の高さ
    camPos_.z = pPlayer_->GetPosition().z;

    // カメラの位置と焦点を取得
    XMVECTOR camPosVector = XMLoadFloat3(&camPos_);
    XMVECTOR forwardVector = XMVector3TransformCoord(XMLoadFloat3(&FORWARD_VECTOR), mView);

    /////////////////加算する前にプレイヤークラスに見ている方向を伝える
    XMStoreFloat3(&aimDirection_, forwardVector); 
    ///////////////

    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    // カメラの位置と焦点を設定
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);

    eyePositon_ = camPosFloat3;

    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}

// 描画
void Aim::Draw()
{
    // クロスヘアを表示
    pNum_->Draw(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2, "+");
}

// 開放
void Aim::Release()
{
}

