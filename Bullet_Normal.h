#pragma once
#include "BulletBase.h"

class BulletBase;

// 銃弾を管理するクラス
class Bullet_Normal : public BulletBase
{
    int hModel_;            // モデル番号    

public:
    Bullet_Normal(GameObject* parent);
    ~Bullet_Normal();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    
    // 何かに当たった時
    void OnCollision(GameObject* pTarget);
};