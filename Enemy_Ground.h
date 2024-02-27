#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// �n��G���Ǘ�����N���X
class Enemy_Ground : public EnemyBase
{
    int hModel_;                        // ���f���ԍ�
    SphereCollider* pCollision_;        // �R���W����
    float lastAngle_;
public:
    Enemy_Ground(GameObject* parent);   // �R���X�g���N�^
    ~Enemy_Ground() override;           // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V

    // ���όv�Z
    float CalculateDotProduct(const XMFLOAT3& directionToPlayer);

    // �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
    void ApproachPlayer(const XMFLOAT3& directionToPlayer);

    // �G�̑̂��v���C���[�̕����։�]������
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer);

    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    void Attack() override;

};
