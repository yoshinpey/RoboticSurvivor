#pragma once
#include "BulletBase.h"

class BulletBase;
class Gun;

// �e�e���Ǘ�����N���X
class Bullet_Explosion : public BulletBase
{
    int hModel_; 
    int hSound_;
    Gun* pGun_;
    bool IsBulletHit;
    bool isFirstHit;

public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void RotateToTarget(const XMFLOAT3& directionToPlayer);
};