#include "Enemy_Fly.h"

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pCollision_(nullptr)
{
    // プレイヤーのステータスを設定
    //characterStatus_.SetCharacterStatus(MAX_HP, ATK);
    //characterStatus_.SetMovementParameters(JUMP_HEIGHT, WALK_SPEED, RUN_SPEED);

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

/*
void Enemy_Ground::loadStatsFromXML(const std::string& filename)
{
    ////////////////////これインクルード
    // #include "pugixml.hpp"
    //
    /////////////////////////////これコンストラクタ
    // XMLファイルからステータスを読み込む
    // なぜかデータ入らんかった
    //loadStatsFromXML("EnemySettings.xml");
    //
    /////////////////////これこのまま
    //pugi::xml_document doc;
    //if (!doc.load_file(filename.c_str())) {
    //    // XMLファイルの読み込みに失敗した場合の処理
    //    return;
    //}
    //// XMLノードからステータスを取得
    //pugi::xml_node rootNode = doc.child("Enemy_Ground");
    //if (!rootNode) {
    //    // Enemy_Groundノードが見つからなかった場合の処理
    //    return;
    //}
    //walkSpeed_ = std::stof(rootNode.child("walkSpeed").text().get());
    //attackPower_ = std::stof(rootNode.child("attackPower").text().get());
    //attackCooldown_ = std::stof(rootNode.child("attackCooldown").text().get());
}

// JSONファイルから歩く速さを読み込む関数
void Enemy_Ground::LoadWalkSpeedFromJson(const std::string& filename)
{
    ////////////////////これインクルード
    //#include <fstream>
    //#include "picojson.h"
    //////////////////////////これコンストラクタ
    // JSONファイルから歩く速さを読み込む
    //walkSpeed_ = LoadWalkSpeedFromJson("EnemySettings.json");
    ///////////////////////////これこのまま
    //picojson::value json_data;
    //// JSONファイルを読み込む
    //std::ifstream file("EnemySettings.json");
    //if (!file.is_open()) {
    //    return;
    //}
    //// picojson::valueにJSONデータをパースする
    //file >> json_data;
    //file.close();
    //// JSONオブジェクトからEnemy_Groundの歩く速さを取得する
    //// 歩く速さを取得してメンバ変数に設定する
    //walkSpeed_ = json_data.get<picojson::object>()
    //    ["Enemy_Ground"].get<picojson::object>()
    //    ["walk_speed"].get<double>();
}
*/
