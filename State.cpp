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

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �E�H�[�N�L�[�������ꂽ��
    if (InputManager::IsRun()) { pStateManager_->ChangeState("WalkingState"); }
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
    OutputDebugString("aaa");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->CalculateMoveInput();
    pPlayer->Walk();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �_�b�V���L�[�������ꂽ��
    if (InputManager::IsRun()) { pStateManager_->ChangeState("RunningState"); }
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
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->CalculateMoveInput();
    pPlayer->Walk();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()){pStateManager_->ChangeState("RunningState");}
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
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Jump();
}

void JumpingState::ExitState()
{
}
