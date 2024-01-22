#pragma once
#include "Engine/GameObject.h"

// �G�l�~�[�̖��O��ID���Ǘ�����enum
enum class EnemyType
{
    FLY,
    GROUND,
};

// �G�l�~�[�x�[�X�N���X
class EnemyBase : public GameObject
{
private:
    EnemyType enemyType_;  // �G�l�~�[�̎��

public:
    // �R���X�g���N�^
    EnemyBase(EnemyType enemyType)
        : GameObject(), enemyType_(enemyType)
    {
    }

    virtual ~EnemyBase() = 0;
    virtual void Update() = 0;

    // �G�l�~�[�̎�ނ��擾
    EnemyType GetEnemyType() const { return enemyType_; }

    virtual std::string GetName() const = 0;
    virtual int GetId() const = 0;
};