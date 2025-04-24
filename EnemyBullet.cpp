//#include "EnemyBullet.h"
//
//#include "Engine/SphereCollider.h"
//#include "Engine/Model.h"
//
//#include "Character.h"
//
//namespace 
//{
//    const XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };       // 当たり判定の位置
//    const std::string modelName = "Model/Bullet.fbx";            // モデル名
//}
//
//EnemyBullet::EnemyBullet(GameObject* parent, std::string name)
//    :GameObject(parent, name), moveDirection_(0, 0, 0), pCollision_(nullptr)
//{
//}
//
//void EnemyBullet::Initialize()
//{
//    damage_ = 1.0f;         // ダメージ
//    speed_ = 0.3f;          // 速度
//    killTimer_ = 180;       // 弾丸の寿命
//    collisionScale_ = 0.3f; // 判定サイズ
//
//    // 当たり判定の追加
//    pCollision_ = new SphereCollider(this);
//    pCollision_->SetRadius(collisionScale_);
//    pCollision_->SetTag("EnemyBullet");
//    CollisionManager::GetInstance()->AddCollider(pCollision_);
//
//    // モデルの設定（任意）
//    SetModel(ModelManager::GetInstance()->GetModel("bullet_model"));
//
//    // 座標の初期化など
//}
//
//void EnemyBullet::Update()
//{
//    // 移動
//    transform_.position.x += moveDirection_.x * speed_;
//    transform_.position.y += moveDirection_.y * speed_;
//    transform_.position.z += moveDirection_.z * speed_;
//
//    // 当たり判定の更新
//    if (pCollision_) {
//        pCollision_->SetPosition(transform_.position);
//    }
//
//    // 寿命による削除
//    if (--killTimer_ <= 0) {
//        SetIsDead(true);
//    }
//}
//
//void EnemyBullet::OnCollision(GameObject* other)
//{
//    // プレイヤーに当たった場合
//    if (other->GetTag() == "Player") {
//        Player* player = dynamic_cast<Player*>(other);
//        if (player) {
//            player->TakeDamage(damage_);
//        }
//        SetIsDead(true); // 弾を消す
//    }
//
//    // 敵に当たった場合（フレンドリーファイア無効：何もしない）
//    else if (other->GetTag() == "Enemy") {
//        // 無視
//    }
//
//    // 地形など他のものに当たった場合
//    else {
//        SetIsDead(true);
//    }
//}
//
//void EnemyBullet::Draw()
//{
//    // 任意のモデル描画処理
//    GameObject::Draw();
//}
//
//void EnemyBullet::Release()
//{
//    if (pCollision_) {
//        CollisionManager::GetInstance()->RemoveCollider(pCollision_);
//        delete pCollision_;
//        pCollision_ = nullptr;
//    }
//}
