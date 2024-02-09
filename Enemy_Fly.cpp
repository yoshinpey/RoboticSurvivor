#include "Enemy_Fly.h"
#include "JsonReader.h"

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pCollision_(nullptr)
{
    // プレイヤーのステータスを設定
    //characterStatus_.SetCharacterStatus(MAX_HP, ATK);
    //characterStatus_.SetMovementParameters(JUMP_HEIGHT, WALK_SPEED, RUN_SPEED);

    // Jsonファイルからステータスとアルゴリズムを読み込む
    JsonReader reader("Assets/EnemySetings.json");
    if (reader.loadJsonData())
    {
        auto& data = reader.getData();
        auto& status = data["Enemy_Fly"]["status"];
        auto& algorithm = data["Enemy_Fly"]["algorithm"];

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

Enemy_Fly::~Enemy_Fly()
{
}

void Enemy_Fly::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Character/Enemy.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // 当たり判定付与
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 1.5f);
    AddCollider(pCollision_);
}

void Enemy_Fly::Update()
{
    // コリジョンの大きさをモデルに合わせる
    // pCollision_->SetRadius(transform_.scale_.x);
}

void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Fly::Release()
{
}

void Enemy_Fly::OnCollision(GameObject* pTarget)
{
    /*
    // 銃弾に当たったとき
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Fly::Attack()
{
}
