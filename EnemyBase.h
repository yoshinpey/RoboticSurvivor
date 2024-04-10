#pragma once
#include "Engine/GameObject.h"
#include "Player.h"

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
    EnemyType enemyType_;  // �G�l�~�[�̎��
    
    // �e�X�e�[�^�X
    struct EnemyStatus
    {
        float walkSpeed_;       // �ړ����x
        int attackPower_;       // �U����
        int attackCooldown_;    // �U���p�x
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
    EnemyStatus status_;
    EnemyAlgorithm algorithm_;


public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
        : GameObject(parent, name), enemyType_(enemyType)
    {
        status_ = { 0,0,0 };
        algorithm_ = { 0,0,0,0 };    

    }

    virtual ~EnemyBase() = default;

    // �G�̎�ނ��擾
    EnemyType GetEnemyType() const { return enemyType_; }

    // �U��
    virtual void Attack() = 0;

    // �v���C���[�Ƃ̋������Z�o����
    float CheckPlayerDistance() {
        Player* pPlayer_ = static_cast<Player*>(FindObject("Player"));
        return CalculateDistance(this->GetPosition(), pPlayer_->GetPosition());

    }

    // �v���C���[�ւ̕������Z�o����
    virtual XMFLOAT3 CheckPlayerDirection() = 0;

    // ���όv�Z(����p�v�Z)
    virtual float CalculateDotProduct(const XMFLOAT3& directionToPlayer) = 0;

    // �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
    virtual void ApproachPlayer(const XMFLOAT3& directionToPlayer) = 0;

    // �G�̑̂��v���C���[�̕����։�]������
    virtual void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer) = 0;
};