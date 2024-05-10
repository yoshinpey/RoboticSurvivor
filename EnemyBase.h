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
        float collisionScale_;  // �����蔻��̑傫��
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
    bool isFirstHit_;               // ����q�b�g�ŗ��Ă�t���O

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
    float GetCurrentHp() const { return currentHp_; }

    // HP�𑝂₷
    void IncreaseHp(float amount) {
        currentHp_ += amount;
        if (currentHp_ > status_.maxHp_) {
            currentHp_ = status_.maxHp_;
        }
    }

    // HP�����炷
    void DecreaseHp(float amount) {
        currentHp_ -= amount;
        if (currentHp_ < 0) {
            currentHp_ = 0;
        }
    }

    // ���S����
    bool IsDead() { 
        bool b = (currentHp_ <= 0.0f); 
        return b;
    }

};