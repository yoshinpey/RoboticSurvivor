#pragma once
#include "BulletBase.h"

class BulletBase;

// e’e‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class Bullet_Normal : public BulletBase
{
    int hModel_;            // ƒ‚ƒfƒ‹”Ô†    
    XMFLOAT3 move_;         // ’e‚Ì“®‚«

public:
    Bullet_Normal(GameObject* parent);
    ~Bullet_Normal();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    
    BulletParameter parameter_;
 
    // ‰½‚©‚É“–‚½‚Á‚½
    void OnCollision(GameObject* pTarget);

    // ’e‚Ì“®‚«İ’è—p
    void SetMove(XMFLOAT3 move) { move_ = move; }
};