#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Normal.h"

#include "JsonReader.h"
//#include "AudioManager.h"
//#include "EffectManager.h"
#include "Character.h"

namespace
{
    const XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };        // 当たり判定の位置
    const std::string modelName = "Entity/Bullet.fbx";            // モデル名
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

    // 弾の生存時間処理
    if (parameter_.killTimer_ > 0) parameter_.killTimer_--;    // 弾の生存タイマーを減らす
    else KillMe();
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
    // 地面関連の物体に当たったとき
    if (pTarget->GetObjectName().find("Stage") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }

    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // すでにこの敵に対してヒット済みの場合は無視
        if (hitEnemies.find(pTarget) != hitEnemies.end()) return;

        // Characterにキャスト
        Character* pCharacter = dynamic_cast<Character*>(pTarget);

        // ダメージを与える
        pCharacter->DecreaseHp(parameter_.damage_);

        // 貫通しない場合は弾丸を消す.貫通する場合はヒットを記録
        if (parameter_.isPenetration_ == 0)  parameter_.killTimer_ = 0;     
        else hitEnemies.insert(pTarget);
    }
}
