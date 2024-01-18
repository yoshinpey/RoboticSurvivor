#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Gun.h"

const float Aim::EYE_POSITION = 2.0f;
const float Aim::MOUSE_SENSITIVITY_X = 0.05f;
const float Aim::MOUSE_SENSITIVITY_Y = 0.05f;

// コンストラクタ
Aim::Aim(GameObject* parent) : GameObject(parent, "Aim"), pNum_(nullptr), pPlayer_(nullptr),
aimDirection_{ 0,0,0 }, camPos_{0,0,0}, mouseSensitivity_ {MOUSE_SENSITIVITY_X, MOUSE_SENSITIVITY_Y}
{
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

    // マウス座標テキスト
    pNum_ = new Text;
    pNum_->Initialize();

    // 銃はカメラにくっつく
    Instantiate<Gun>(this);

    //マウス初期位置(幅/2, 高さ/2)
    Input::SetMousePosition(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2);

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
    XMFLOAT3 mouseMove = Input::GetMouseMove();
    transform_.rotate_.y += mouseMove.x * mouseSensitivity_.x;
    transform_.rotate_.x += mouseMove.y * mouseSensitivity_.y;
}

void Aim::UpdateCameraPosition() 
{
    // カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mView = mRotX * mRotY;

    XMFLOAT3 plaPos = pPlayer_->GetPlaPos();

    // カメラ位置の計算
    camPos_.x = plaPos.x;
    camPos_.y = plaPos.y + EYE_POSITION; // 目線の高さ
    camPos_.z = plaPos.z;

    // カメラの位置と焦点を取得
    XMVECTOR camPosVector = XMLoadFloat3(&camPos_);
    XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forwardVector = XMVector3TransformCoord(forwardVector, mView);
    XMStoreFloat3(&aimDirection_, forwardVector); //プレイヤークラスに進行方向ベクトル(float3)を伝える

    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    // カメラの位置と焦点を設定
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);

    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}
// 描画
void Aim::Draw()
{
    pNum_->Draw(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2, "+");
}

// 開放
void Aim::Release()
{
}

