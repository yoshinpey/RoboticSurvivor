#include "Enemy_Ground.h"
#include "pugixml.hpp"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr)
{
    // XMLファイルからステータスを読み込む
    loadStatsFromXML("EnemySettings.xml");
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
    if (walkSpeed_ <= 0.3)
    {
        transform_.position_.x += 0.01;
    }
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

void Enemy_Ground::loadStatsFromXML(const std::string& filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str())) {
        // XMLファイルの読み込みに失敗した場合の処理
        return;
    }

    // XMLノードからステータスを取得
    pugi::xml_node rootNode = doc.child("Enemy_Ground");
    if (!rootNode) {
        // Enemy_Groundノードが見つからなかった場合の処理
        return;
    }

    walkSpeed_ = std::stof(rootNode.child("walkSpeed").text().get());
    attackPower_ = std::stof(rootNode.child("attackPower").text().get());
    attackCooldown_ = std::stof(rootNode.child("attackCooldown").text().get());
}