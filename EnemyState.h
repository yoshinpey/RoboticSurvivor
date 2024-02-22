#pragma once

class EnemyBase;
class StateBase;
class StateManager;

// �ҋ@���
class EnemyIdleState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// �p�j���G���
class EnemyWanderingState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyWanderingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// �����ǐՏ��
class EnemyChaseState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyChaseState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// �U�����
class EnemyAttackState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyAttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// �_���[�W���
class EnemyDamageState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyDamageState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};