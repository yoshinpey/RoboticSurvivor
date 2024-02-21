#pragma once
#include "StateBase.h"

class EnemyBase;
class StateBase;
class StateManager;

// �G�l�~�[�ҋ@���
class EnemyIdleState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// �G�l�~�[�ǐՏ��
class EnemyChaseState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyChaseState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// �G�l�~�[�U�����
class EnemyAttackState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyAttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// �G�l�~�[�_���[�W���
class EnemyDamageState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyDamageState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
