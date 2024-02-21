#include "EnemyState.h"
#include "EnemyBase.h"
#include "StateManager.h"

// エネミー待機状態
EnemyIdleState::EnemyIdleState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyIdleState::EnterState()
{
    // 待機状態に入った時の処理
}

void EnemyIdleState::UpdateState()
{
    // 待機状態の更新
}

void EnemyIdleState::ExitState()
{
    // 待機状態から出る時の処理
}

// エネミー追跡状態
EnemyChaseState::EnemyChaseState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyChaseState::EnterState()
{
    // 追跡状態に入った時の処理
}

void EnemyChaseState::UpdateState()
{
    // 追跡状態の更新
}

void EnemyChaseState::ExitState()
{
    // 追跡状態から出る時の処理
}

// エネミー攻撃状態
EnemyAttackState::EnemyAttackState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyAttackState::EnterState()
{
    // 攻撃状態に入った時の処理
}

void EnemyAttackState::UpdateState()
{
    // 攻撃状態の更新
}

void EnemyAttackState::ExitState()
{
    // 攻撃状態から出る時の処理
}

// エネミーダメージ状態
EnemyDamageState::EnemyDamageState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyDamageState::EnterState()
{
    // ダメージ状態に入った時の処理
}

void EnemyDamageState::UpdateState()
{
    // ダメージ状態の更新
}

void EnemyDamageState::ExitState()
{
    // ダメージ状態から出る時の処理
}
