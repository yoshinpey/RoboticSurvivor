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
    EnemyBase(GameObject* parent, EnemyType enemyType)
        : GameObject(parent), enemyType_(enemyType)
    {
    }

    virtual ~EnemyBase() = default;

    // �G�l�~�[�̎�ނ��擾
    EnemyType GetEnemyType() const { return enemyType_; }

    // �������z�֐�
    virtual void Update() = 0;
};