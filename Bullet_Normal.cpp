#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Normal.h"
#include "JsonReader.h"
#include "EnemyBase.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };        // 当たり判定の位置
    std::string modelName = "Entity/Bullet.fbx";            // モデル名
}

//コンストラクタ
Bullet_Normal::Bullet_Normal(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Normal"), hModel_(-1)
{
    // JSONファイル読み込み
    JsonReader::Load("Settings/WeaponSettings.json");
    auto& bullet_normal = JsonReader::GetSection("Bullet_Normal");

    // パラメータを取得
    parameter_.damage_ = bullet_normal["damage"];
    parameter_.shotCoolTime_ = bullet_normal["shotCoolTime"];
    parameter_.speed_ = bullet_normal["speed"];
    parameter_.killTimer_ = bullet_normal["killTimer"];
    parameter_.collisionScale_ = bullet_normal["collisionScale"];
    parameter_.isPenetration_ = bullet_normal["isPenetration"];
}

//デストラクタ
Bullet_Normal::~Bullet_Normal()
{
}

//初期化
void Bullet_Normal::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    //当たり判定
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);
}

//更新
void Bullet_Normal::Update()
{
    //弾を飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    //弾を消す
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) { KillMe(); }
}

//描画
void Bullet_Normal::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet_Normal::Release()
{
}

void Bullet_Normal::OnCollision(GameObject* pTarget)
{
    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // EnemyBaseにキャスト
        Character* chara = dynamic_cast<Character*>(pTarget);

        // ダメージを与える
        chara->DecreaseHp(GetBulletParameter().damage_);

        KillMe();
    }
}
