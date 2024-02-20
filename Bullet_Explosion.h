#pragma once
#include "BulletBase.h"

class BulletBase;

// e’e‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class Bullet_Explosion : public BulletBase
{
    int hModel_;            // ƒ‚ƒfƒ‹”Ô†    
public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget)override;
};