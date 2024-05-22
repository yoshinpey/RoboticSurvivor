#pragma once
#include "BulletBase.h"
#include <unordered_set>

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

    // �q�b�g�����G�̃f�[�^�����Ă���
    std::unordered_set<GameObject*> hitEnemies;

public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void RotateToTarget(XMFLOAT3& directionToPlayer);

    void OnCollision(GameObject* pTarget);
};