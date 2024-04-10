#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

class Player;

// �n��G���Ǘ�����N���X
class Enemy_Ground : public EnemyBase
{
    int hModel_;                        // ���f���ԍ�
    Player* pPlayer_;
    float lastAngle_;

public:
    Enemy_Ground(GameObject* parent);   // �R���X�g���N�^
    ~Enemy_Ground() override;           // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V
    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    // �U��
    void Attack() override;

    // �v���C���[�Ƃ̋������Z�o����
    //float CheckPlayerDistance() override;

    // �v���C���[�ւ̕������Z�o����
    XMFLOAT3 CheckPlayerDirection() override;

    // ���όv�Z(����p�v�Z)
    float CalculateDotProduct(const XMFLOAT3& directionToPlayer) override;

    // �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
    void ApproachPlayer(const XMFLOAT3& directionToPlayer) override;

    // �G�̑̂��v���C���[�̕����։�]������
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer) override;
};
