#include "EnemyState.h"
#include "EnemyBase.h"
#include "StateManager.h"

// �G�l�~�[�ҋ@���
EnemyIdleState::EnemyIdleState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyIdleState::EnterState()
{
    // �ҋ@��Ԃɓ��������̏���
}

void EnemyIdleState::UpdateState()
{
    // �ҋ@��Ԃ̍X�V
}

void EnemyIdleState::ExitState()
{
    // �ҋ@��Ԃ���o�鎞�̏���
}

// �G�l�~�[�ǐՏ��
EnemyChaseState::EnemyChaseState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyChaseState::EnterState()
{
    // �ǐՏ�Ԃɓ��������̏���
}

void EnemyChaseState::UpdateState()
{
    // �ǐՏ�Ԃ̍X�V
}

void EnemyChaseState::ExitState()
{
    // �ǐՏ�Ԃ���o�鎞�̏���
}

// �G�l�~�[�U�����
EnemyAttackState::EnemyAttackState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyAttackState::EnterState()
{
    // �U����Ԃɓ��������̏���
}

void EnemyAttackState::UpdateState()
{
    // �U����Ԃ̍X�V
}

void EnemyAttackState::ExitState()
{
    // �U����Ԃ���o�鎞�̏���
}

// �G�l�~�[�_���[�W���
EnemyDamageState::EnemyDamageState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyDamageState::EnterState()
{
    // �_���[�W��Ԃɓ��������̏���
}

void EnemyDamageState::UpdateState()
{
    // �_���[�W��Ԃ̍X�V
}

void EnemyDamageState::ExitState()
{
    // �_���[�W��Ԃ���o�鎞�̏���
}
