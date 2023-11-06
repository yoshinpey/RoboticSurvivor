#include "Engine/BoxCollider.h"
#include "Engine/Model.h"

#include "Ground.h"


//コンストラクタ
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{
}

//デストラクタ
Ground::~Ground()
{
}

//初期化
void Ground::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Stage/Ground.fbx");
    assert(hModel_ >= 0);

    //あたり判定
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, -4, 0), XMFLOAT3(5, 7, 5));
    AddCollider(collision);
}

//更新
void Ground::Update()
{
}

//描画
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ground::Release()
{
}

//あたり判定
void Ground::OnCollision(GameObject* pTarget)
{
    //弾に当たったとき
    if (pTarget->GetObjectName() == "Bullet")
    {

    }

    //敵に当たったとき
    if (pTarget->GetObjectName() == "Enemy")
    {

    }

    //プレイヤーに当たったとき
    if (pTarget->GetObjectName() == "Player")
    {

    }

}
