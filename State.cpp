#include "State.h"
#include "Player.h"
#include "StateManager.h"


// �ҋ@���
IdleState::IdleState(StateManager* manager) : StateBase(manager)
{
}
void IdleState::EnterState()
{
}

void IdleState::UpdateState()
{
}

void IdleState::ExitState()
{
}


// ���s���
WalkingState::WalkingState(StateManager* manager) : StateBase(manager)
{
}

void WalkingState::EnterState()
{
}

void WalkingState::UpdateState()
{   
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());

    // �����v�Z
    pPlayer->CalculateMoveInput();

    // �W�����v�L�[�������ꂽ��W�����v��ԂɑJ��
    if (InputManager::IsJump())
    {
        pStateManager_->ChangeState(new JumpingState(pStateManager_));
    }

    pPlayer->Move();

    // ������K�p
    pPlayer->CalculateMoveInput();


    // �W�����v�L�[�������ꂽ��W�����v��ԂɑJ��
    if (InputManager::IsJump())
    {
        pStateManager_->ChangeState(new JumpingState(pStateManager_));
    }
}

void WalkingState::ExitState()
{
}


// ���s���
RunningState::RunningState(StateManager* manager) : StateBase(manager)
{
}

void RunningState::EnterState()
{
}

void RunningState::UpdateState()
{

    // �W�����v�L�[�������ꂽ��W�����v��ԂɑJ��
    if (InputManager::IsJump())
    {
        pStateManager_->ChangeState(new JumpingState(pStateManager_));
    }
}

void RunningState::ExitState()
{
}


// ������
JumpingState::JumpingState(StateManager* manager) : StateBase(manager)
{
}

void JumpingState::EnterState()
{
}

void JumpingState::UpdateState()
{
}

void JumpingState::ExitState()
{
}
