#pragma once
#include "BulletBase.h"

class BulletBase;

// �e�e���Ǘ�����N���X
class Bullet_Normal : public BulletBase
{
    int hModel_;    
public:
    Bullet_Normal(GameObject* parent);
    ~Bullet_Normal();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget);

};