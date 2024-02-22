#pragma once

class EnemyBase;
class StateBase;
class StateManager;

// 待機状態
class EnemyIdleState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 徘徊索敵状態
class EnemyWanderingState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyWanderingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 発見追跡状態
class EnemyChaseState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyChaseState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 攻撃状態
class EnemyAttackState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyAttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ダメージ状態
class EnemyDamageState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyDamageState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};