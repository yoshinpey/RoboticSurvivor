#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// �n��G���Ǘ�����N���X
class Enemy_Ground : public EnemyBase
{
    int hModel_;                        // ���f���ԍ�
    SphereCollider* pCollision_;        // �R���W����

public:
    Enemy_Ground(GameObject* parent);   // �R���X�g���N�^
    ~Enemy_Ground() override;           // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V
    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    void Attack() override;
};
