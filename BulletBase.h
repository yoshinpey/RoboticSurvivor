#pragma once
#include "Engine/GameObject.h"

// 弾丸の名前とIDを管理するenum
enum class BulletType
{
    NORMAL,
    EXPLOSION,
    MAX
};

// 銃弾の基底クラス
class BulletBase : public GameObject
{
private:
    BulletType bulletType_;
    // バレットの共通パラメータ
    struct BulletParameter
    {
        float damage_;          // ダメージ
        int shotCoolTime_;      // クールタイム
        float speed_;           // スピード
        int killTimer_;         // 消失時間
        float collisionScale_;  // 当たり判定のサイズ
        int isPenetration_;     // 貫通   あり:1 なし:0
    };
protected:
    BulletParameter parameter_; // パラメータ
    XMFLOAT3 move_;             // 移動の速度と方向
    SphereCollider* pCollision_; // パラメータ

public:
    BulletBase(GameObject* parent, BulletType bulletType, std::string name)
        :GameObject(parent, name), bulletType_(bulletType), move_(0,0,0), parameter_{ 0, 0, 0, 0, 0, false }, pCollision_(nullptr)
    {
    };
    virtual ~BulletBase() = default;

    // 銃弾の種類を取得
    BulletType GetBulletType() const { return bulletType_; }

    // 銃弾のパラメータを取得
    BulletParameter GetBulletParameter() const { return parameter_; }

    // 銃弾の移動を設定
    void SetMove(const XMFLOAT3& move) { move_ = move; }
};