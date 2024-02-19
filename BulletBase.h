#pragma once
#include "Engine/GameObject.h"

// 弾丸の名前とIDを管理するenum
enum class BulletType
{
    NORMAL,
    EXPLOSION
};

// 銃弾の基底クラス
class BulletBase : public GameObject
{
private:
    BulletType bulletType_;

public:
    BulletBase(GameObject* parent, BulletType bulletType, std::string name)
        :GameObject(parent, name), bulletType_(bulletType)
    {
    };

    virtual ~BulletBase() = default;

    // バレットの共通パラメータ
    struct BulletParameter
    {
        float killTimer_;       // 消失時間
        float speed_;           // スピード
        float damage_;          // ダメージ
        float shotCoolTime_;    // クールタイム
        float collisionSize_;   // 当たり判定のサイズ
        bool penetrationPower_; // 貫通   あり:1 なし:0
    };

    // バレットの種類を取得
    BulletType GetBulletType() const { return bulletType_; }

    // 攻撃
    virtual void Attack() = 0;
};