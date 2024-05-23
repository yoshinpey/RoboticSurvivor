#pragma once
#include "BulletBase.h"
#include <unordered_set>

class BulletBase;

// �e�e���Ǘ�����N���X
class Bullet_Explosion : public BulletBase
{
    int hModel_;
    float verticalSpeed_;   // ���������̃X�s�[�h�ϐ�

    // �q�b�g�����G�̃f�[�^�����Ă���
    std::unordered_set<GameObject*> hitEnemies;

public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget);

    // �e�̌�����Ώە����։�]������
    void RotateToTarget(XMFLOAT3& directionToPlayer);

};