#include "Enemy_Ground.h"
#include "JsonReader.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr)
{
    // Jsonファイルからステータスとアルゴリズムを読み込む
    JsonReader reader("Assets/EnemySetings.json");
    if (reader.loadJsonData())
    {
        auto& data = reader.getData();
        auto& status = data["Enemy_Ground"]["status"];
        auto& algorithm = data["Enemy_Ground"]["algorithm"];

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

Enemy_Ground::~Enemy_Ground()
{
}

void Enemy_Ground::Initialize()
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

void Enemy_Ground::Update()
{
}

void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{
    /*
    // 銃弾に当たったとき
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Ground::Attack()
{
}
