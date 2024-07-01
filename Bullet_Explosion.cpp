#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"

#include "JsonReader.h"
#include "AudioManager.h"
#include "EffectManager.h"
#include "Character.h"
#include "EnemyBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    const XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };    // 当たり判定の位置
    const XMFLOAT3 modelScale = { 0.2f, 0.2f, 0.2f };         // モデルのサイズ
    const std::string modelName = "Entity/Missile.fbx";       // モデル名

    const float explosionVolume = 0.1f;

    //////////////////////////////
    const float gravity = -0.0025f;          // 銃弾にかける重力
    const float accelerationLimit = -0.4f;   // 加速限界
    const int modelRotate = 180;             // モデル回転
}

//コンストラクタ
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::EXPLOSION, "Bullet_Explosion"), hModel_(-1), verticalSpeed_(0.0f)
{
    // JSONファイル読み込み
    JsonReader::Load("Settings/WeaponSettings.json");
    auto& bullet_explosion = JsonReader::GetSection("Bullet_Explosion");

    // パラメータを取得
    parameter_.damage_ = bullet_explosion["damage"];
    parameter_.shotCoolTime_ = bullet_explosion["shotCoolTime"];
    parameter_.speed_ = bullet_explosion["speed"];
    parameter_.killTimer_ = bullet_explosion["killTimer"];
    parameter_.collisionScale_ = bullet_explosion["collisionScale"];
    explodeScale_ = bullet_explosion["explodeScale"];
    parameter_.magazineSize_ = bullet_explosion["magazineSize"];
    parameter_.reloadTime_ = bullet_explosion["reloadTime"];
}

//デストラクタ
Bullet_Explosion::~Bullet_Explosion()
{
}

//初期化
void Bullet_Explosion::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    transform_.scale_ = modelScale;

    //当たり判定
    AddCollider(new SphereCollider(collisionOffset, parameter_.collisionScale_));
}

//更新
void Bullet_Explosion::Update()
{
    // 加速度制限
    if(verticalSpeed_ >= accelerationLimit) verticalSpeed_ += gravity;
    
    // 位置を保存する
    XMFLOAT3 previousPosition = transform_.position_;

    // 重力を加算して放物線運動させる
    transform_.position_.y += verticalSpeed_;

    // 銃クラスであらかじめ計算していた方向(銃口の先)へ飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // モデルの向きを合わせる
    XMFLOAT3 targetVector = CalculateDirection(transform_.position_, previousPosition);
    RotateToTarget(targetVector);

    // 弾の生存時間処理
    if (parameter_.killTimer_ > 0)
    { 
        // 弾の生存タイマーを減らす
        parameter_.killTimer_--;
    }
    else
    {
        // 爆発する
        AudioManager::Play(AUDIO_ID::EXPLODE, explosionVolume);
        EffectManager::CreateVfx(transform_.position_, VFX_TYPE::EXPLODE);

        // 敵との距離を計測し、範囲内だったら与ダメージ
        EnemyManager* pEnemyManager = static_cast<PlayScene*>(FindObject("PlayScene"))->GetEnemyManager();
        // エネミーリストから距離の条件を満たす敵を探す
        for (EnemyBase* e : pEnemyManager->GetEnemyList())
        {
            XMFLOAT3 enePos = e->GetPosition();
            float dist = CalculateDistance(transform_.position_, enePos);
            if (dist < explodeScale_)
            {
                e->DecreaseHp(parameter_.damage_);
                e->BulletHit();
            }
        }
        KillMe();
    }
}

//描画
void Bullet_Explosion::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet_Explosion::Release()
{
}

// 弾の向きを対象方向へ回転させる
void Bullet_Explosion::RotateToTarget(XMFLOAT3& targetVector)
{
    XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f};
    rot.x = XMConvertToDegrees(asinf(targetVector.y));
    rot.y = XMConvertToDegrees(atan2f(targetVector.x, targetVector.z)) + modelRotate;    // モデルの向き逆だったから反転
    transform_.rotate_ = rot;
}


void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
    
    // 地面関連の物体に当たったとき
    if (pTarget->GetObjectName().find("Stage") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
};