#pragma once
#include "Engine/GameObject.h"

// �G�l�~�[�̖��O��ID���Ǘ�����enum
enum class EnemyType
{
    FLY,
    GROUND,
    EXPLOSION,
    MAX
};

// �G�l�~�[�x�[�X�N���X
class EnemyBase : public GameObject
{
private:

    // �e�X�e�[�^�X
    struct EnemyStatus
    {
        float walkSpeed_;       // �ړ����x
        int attackPower_;       // �U����
        int attackCooldown_;    // �U���p�x
        float maxHp_;           // �̗�
    };

    // �A���S���Y��
    struct EnemyAlgorithm
    {
        int detectPlayerDistance_;  // �v���C���[�܂ł̋���
        int patrolRadius_;          // �v���C���[�����m���鋗��
        int approachDistance_;      // �v���C���[�֐ڋ߂��鋗��
        int attackDistance_;        // �v���C���[�֍U���������鋗��
    };

protected:
    // �\���̂̃C���X�^���X
    EnemyStatus status_;            // �X�e�[�^�X
    EnemyAlgorithm algorithm_;      // �s��
    EnemyType enemyType_;           // �G�l�~�[�̎��
    float currentHp_;               // ���݂�HP 

public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name);

    virtual ~EnemyBase() = default;

    // �G�̎�ނ��擾
    EnemyType GetEnemyType() const { return enemyType_; }

    // �U��
    virtual void Attack() = 0;

    // �v���C���[�Ƃ̋������Z�o����
    float CheckPlayerDistance();

    // �v���C���[�ւ̕������Z�o����
    XMFLOAT3 CheckPlayerDirection();

    // ���όv�Z(����p�v�Z)
    float CalculateDotProduct(const XMFLOAT3& directionToPlayer);

    // �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
    void ApproachPlayer(const XMFLOAT3& directionToPlayer);

    // �G�̑̂��v���C���[�̕����։�]������
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer);

    // HP���擾
    virtual float GetCurrentHp() const = 0;

    // HP�𑝂₷
    virtual void IncreaseHp(float amount) = 0;

    // HP�����炷
    virtual void DecreaseHp(float amount) = 0;

    // ���S����
    virtual bool IsDead() const = 0;
};