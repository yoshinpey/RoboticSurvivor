#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Gun.h"


//コンストラクタ
Aim::Aim(GameObject* parent)
    :GameObject(parent, "Aim"), pNum_(nullptr), pPlayer_(nullptr),
    plaPos_{ 0,0,0 }, camPos_{ 0,0,0 },  aimDirection_{ 0,0,0 }, mouseSensitivity_{MOUSE_SENSITIVITY_X, MOUSE_SENSITIVITY_Y}
{
}

//デストラクタ
Aim::~Aim()
{
}

//初期化
void Aim::Initialize()
{
    //エイムクラスの呼び出し位置
    transform_.position_.y = 2;

    //マウス座標テキスト
    pNum_ = new Text;
    pNum_->Initialize();

    //銃はカメラにつく
    Instantiate<Gun>(this);

    //マウス初期位置(幅/2, 高さ/2)
    Input::SetMousePosition(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2);

    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

//更新
void Aim::Update()
{ 
    //マウス移動量
    XMFLOAT3 mouseMove = Input::GetMouseMove(); // マウスの移動量を取得

    //移動量を加算
    transform_.rotate_.y += mouseMove.x * 0.05f; // 横方向の回転
    transform_.rotate_.x += mouseMove.y * 0.05f; // 縦方向の回転

    ////カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); 

    //カメラの位置と回転を合成
    XMMATRIX mView = mRotX * mRotY;

    //プレイヤー座標取得
    plaPos_ = pPlayer_->GetPlaPos();

    //プレイヤーキャラクターの位置をカメラの位置とする
    camPos_.x = plaPos_.x;
    camPos_.y = plaPos_.y + 2; //目線高さ
    camPos_.z = plaPos_.z;

    //カメラの位置と焦点を取得
    XMVECTOR camPosVector = XMLoadFloat3(&camPos_);
    XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forwardVector = XMVector3TransformCoord(forwardVector, mView);
    XMStoreFloat3(&aimDirection_, forwardVector);   //プレイヤークラスに進行方向ベクトル(float3)を伝える用                    
    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    //カメラの位置と焦点を設定
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);
    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}

//描画
void Aim::Draw()
{
    pNum_->Draw(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2, "+");
}

//開放
void Aim::Release()
{
}
