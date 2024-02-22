#pragma once
#include "StateBase.h"

class EnemyBase;

// ‘Ò‹@ó‘Ô
class EnemyIdleState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// œpœjõ“Gó‘Ô
class EnemyWanderingState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyWanderingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ”­Œ©’ÇÕó‘Ô
class EnemyChaseState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyChaseState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// UŒ‚ó‘Ô
class EnemyAttackState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyAttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ”íƒ_ƒ[ƒWó‘Ô
class EnemyDamageState : public StateBase
{
    EnemyBase* pEnemyBase_;
public:
    EnemyDamageState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};