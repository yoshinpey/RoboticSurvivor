#pragma once
#include "BulletBase.h"

class BulletBase;
class Gun;

// �e�e���Ǘ�����N���X
class Bullet_Explosion : public BulletBase
{
    int hModel_; 
    Gun* pGun_;

    bool isFirstHit_;    // ���߂ē���������

    float gravity_;         // �e�e�ɂ�����d��
    float verticalSpeed_;   // �X�s�[�h

public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void RotateToTarget(const XMFLOAT3& directionToPlayer);

    void OnCollision(GameObject* pTarget);
};