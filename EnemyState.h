#pragma once
#include "StateBase.h"

class EnemyBase;
class StateBase;
class StateManager;

// エネミー待機状態
class EnemyIdleState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// エネミー追跡状態
class EnemyChaseState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyChaseState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// エネミー攻撃状態
class EnemyAttackState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyAttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// エネミーダメージ状態
class EnemyDamageState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyDamageState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
