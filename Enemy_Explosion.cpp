#include "Enemy_Explosion.h"
#include "JsonReader.h"

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1), pCollision_(nullptr)
{
    // Jsonファイルからステータスとアルゴリズムを読み込む
    JsonReader reader("Assets/EnemySetings.json");
    if (reader.loadJsonData())
    {
        auto& data = reader.getData();
        auto& status = data["Enemy_Explosion"]["status"];
        auto& algorithm = data["Enemy_Explosion"]["algorithm"];

        // ステータスを設定
        walkSpeed_ = status["walkSpeed"];
        attackPower_ = status["attackPower"];
        attackCooldown_ = status["attackCooldown"];

        // アルゴリズムを設定
        detectPlayerDistance_ = algorithm["detectPlayerDistance"];
        patrolRadius_ = algorithm["patrolRadius"];
        approachDistance_ = algorithm["approachDistance"];
        attackDistance_ = algorithm["attackDistance"];
    }
}

Enemy_Explosion::~Enemy_Explosion()
{
}

void Enemy_Explosion::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load("Character/Enemy_02.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // 当たり判定付与
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 2.0f);
    AddCollider(pCollision_);
}

void Enemy_Explosion::Update()
{
}

void Enemy_Explosion::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Explosion::Release()
{
}

void Enemy_Explosion::OnCollision(GameObject* pTarget)
{
    /*
    // 銃弾に当たったとき
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Explosion::attack()
{
}
