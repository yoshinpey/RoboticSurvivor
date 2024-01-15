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
    //�f�o�b�N
    OutputDebugString("IdleState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �E�H�[�N�L�[�������ꂽ��
    if (InputManager::IsWalk()){ pStateManager_->ChangeState("WalkingState"); }
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
    //�f�o�b�N
    OutputDebugString("WalkingState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Walk();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �_�b�V���L�[�������ꂽ��
    if (InputManager::IsRun()) { pStateManager_->ChangeState("RunningState"); }

    // �ړ����͂��Ȃ��Ȃ����Ƃ��ҋ@��
    if (!InputManager::IsWalk())
    {
        pStateManager_->ChangeState("IdleState");
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
    //�f�o�b�N
    OutputDebugString("RunningState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Run();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()){pStateManager_->ChangeState("JumpingState");}
}

void RunningState::ExitState()
{
    pStateManager_->ChangeState("IdleState");
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
    //�f�o�b�N
    OutputDebugString("JumpingState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Jump();
}

void JumpingState::ExitState()
{
    pStateManager_->ChangeState("IdleState");
}
