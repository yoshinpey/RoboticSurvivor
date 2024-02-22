#include "EnemyState.h"
#include "EnemyBase.h"
#include "StateManager.h"

// �ҋ@���
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


// �p�j���
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


// �ǐՏ��
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


// �U�����
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


// ��_���[�W���
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