#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// �n��G���Ǘ�����N���X
class Enemy_Explosion : public EnemyBase
{
    int hModel_;  // ���f���ԍ�
    SphereCollider* pCollision_;

    // �e�X�e�[�^�X
    float walkSpeed_;
    float attackPower_;
    float attackCooldown_;
    float detectPlayerDistance_;
    float patrolRadius_;
    float approachDistance_;
    float attackDistance_;

public:
    Enemy_Explosion(GameObject* parent);   // �R���X�g���N�^
    ~Enemy_Explosion() override;           // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V
    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    void Attack() override;
};