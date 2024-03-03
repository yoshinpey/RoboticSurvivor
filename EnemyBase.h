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
        float walkSpeed_;
        int attackPower_;
        int attackCooldown_;
    };

    // �A���S���Y��
    struct EnemyAlgorithm
    {
        int detectPlayerDistance_;
        int patrolRadius_;
        int approachDistance_;
        int attackDistance_;
    };

protected:
    // �\���̂̃C���X�^���X
    EnemyStatus status_;
    EnemyAlgorithm algorithm_;
    Player* pPlayer_;

public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
        : GameObject(parent, name), enemyType_(enemyType), pPlayer_(nullptr)
    {
        status_ = { 0,0,0 };
        algorithm_ = { 0,0,0,0 };    
        // �v���C���[�I�u�W�F�N�g�擾
        pPlayer_ = static_cast<Player*>(FindObject("Player"));
    }

    virtual ~EnemyBase() = default;

    // �G�̎�ނ��擾
    EnemyType GetEnemyType() const { return enemyType_; }

    // �U��
    virtual void Attack() = 0;

    // �v���C���[�Ƃ̋������Z�o����
    float CheckPlayerDistance() 
    {
        return CalculateDistance(this->GetPosition(), pPlayer_->GetPosition());
    }

    // �v���C���[�ւ̕������Z�o����
    XMFLOAT3 CheckPlayerDirection()
    {
        return CalculateDirection(this->GetPosition(), pPlayer_->GetPosition());
    }

    void detectPlayer() {
        // ���E���̃v���C���[�����o���鏈��
    }

    void pathfindToPlayer() {
        // �v���C���[�ɋ߂Â����߂̌o�H�T��
    }

    void patrolInSightRange() {
        // ���E���ł̜p�j
    }

    void approachPlayer() {
        // �v���C���[�ɋ߂Â�
    }
};