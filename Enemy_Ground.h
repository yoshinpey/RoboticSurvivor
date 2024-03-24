#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

class Player;

// �n��G���Ǘ�����N���X
class Enemy_Ground : public EnemyBase
{
    int hModel_;                        // ���f���ԍ�
    SphereCollider* pCollision_;        // �R���W����
    float lastAngle_;
    Player* pPlayer_;
public:
    Enemy_Ground(GameObject* parent);   // �R���X�g���N�^
    ~Enemy_Ground() override;           // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V
    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �v���C���[�Ƃ̋������Z�o����
    float CheckPlayerDistance();

    // �v���C���[�ւ̕������Z�o����
    XMFLOAT3 CheckPlayerDirection();

    // ���όv�Z
    float CalculateDotProduct(const XMFLOAT3& directionToPlayer);

    // �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
    void ApproachPlayer(const XMFLOAT3& directionToPlayer);

    // �G�̑̂��v���C���[�̕����։�]������
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer);

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    // �U��
    void Attack() override;

};
