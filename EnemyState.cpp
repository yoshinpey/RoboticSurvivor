#include "EnemyState.h"
#include "EnemyBase.h"
#include "StateManager.h"

// 待機状態
EnemyIdleState::EnemyIdleState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyIdleState::EnterState()
{
}

void EnemyIdleState::UpdateState()
{
}

void EnemyIdleState::ExitState()
{
}


// 徘徊状態
EnemyWanderingState::EnemyWanderingState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyWanderingState::EnterState()
{
}

void EnemyWanderingState::UpdateState()
{
}

void EnemyWanderingState::ExitState()
{
}


// 追跡状態
EnemyChaseState::EnemyChaseState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyChaseState::EnterState()
{
}

void EnemyChaseState::UpdateState()
{
}

void EnemyChaseState::ExitState()
{
}


// 攻撃状態
EnemyAttackState::EnemyAttackState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyAttackState::EnterState()
{
}

void EnemyAttackState::UpdateState()
{
}

void EnemyAttackState::ExitState()
{
}


// 被ダメージ状態
EnemyDamageState::EnemyDamageState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyDamageState::EnterState()
{
}

void EnemyDamageState::UpdateState()
{
}

void EnemyDamageState::ExitState()
{
}