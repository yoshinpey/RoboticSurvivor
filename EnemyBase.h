#pragma once
#include "Character.h"

// �G�l�~�[�̖��O��ID���Ǘ�����enum
enum class EnemyType
{
    FLY,
    GROUND,
    EXPLOSION,
    MAX
};

// �G�l�~�[�x�[�X�N���X
class EnemyBase : public Character
{
private:
    // �G�l�~�[�̃X�e�[�^�X
    struct EnemyStatus
    {
        int attackPower_;       // �U����
        int attackCooldown_;    // �U���p�x
        float collisionScale_;  // �����蔻��̑傫��
    };

    // �G�l�~�[�̃A���S���Y��
    struct EnemyAlgorithm
    {
        int detectPlayerDistance_;  // �v���C���[�܂ł̋���
        int patrolRadius_;          // ���񔼌a
        int approachDistance_;      // �ڋߋ���
        int attackDistance_;        // �U������
    };

protected:
    EnemyStatus enemyStatus_;       // �G�l�~�[�̃X�e�[�^�X
    EnemyAlgorithm enemyAlgorithm_; // �G�l�~�[�̃A���S���Y��
    EnemyType enemyType_;           // �G�l�~�[�̎��

public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name);

    virtual ~EnemyBase() = default;

    // �G�̎�ނ��擾
    EnemyType GetEnemyType() const { return enemyType_; }

    // �G�̃X�e�[�^�X���擾
    EnemyStatus GetEnemyStatus() const { return enemyStatus_; }

    // �G�̃A���S���Y�����擾
    EnemyAlgorithm GetEnemyAlgorithm() const { return enemyAlgorithm_; }

    // �U��
    virtual void Attack() = 0;

    // �v���C���[�Ƃ̋������Z�o����
    float CheckPlayerDistance();

    // �v���C���[�ւ̕������Z�o����
    XMFLOAT3 CheckPlayerDirection();

    // �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
    void ApproachPlayer(const XMFLOAT3& directionToPlayer);

    // �G�̑̂��v���C���[�̕����։�]������
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer);
};
