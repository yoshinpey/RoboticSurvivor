#pragma once
#include "BulletBase.h"
#include <unordered_set>

class BulletBase;

// 銃弾を管理するクラス
class Bullet_Normal : public BulletBase
{
    int hModel_;    

    // ヒットした敵のデータを入れておく
    std::unordered_set<GameObject*> hitEnemies;

public:
    Bullet_Normal(GameObject* parent);
    ~Bullet_Normal();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget);

};