#pragma once
#include "BulletBase.h"

class BulletBase;

// 銃弾を管理するクラス
class Bullet_Explosion : public BulletBase
{
    int hModel_;            // モデル番号    
public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // 何かに当たった時
    void OnCollision(GameObject* pTarget);

    // バレットのパラメータを取得
    const BulletParameter& GetParameter() const { return parameter_; }
};