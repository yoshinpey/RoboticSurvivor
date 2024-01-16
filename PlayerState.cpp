#include "PlayerState.h"
#include "StateManager.h"
#include "Player.h"



// �ҋ@���
PlayerIdleState::PlayerIdleState(StateManager* manager) : StateBase(manager)
{
}

void PlayerIdleState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerIdleState::UpdateState()
{
    // ���͂��Ȃ��Ƃ��͈ړ������x��K�p����
    pPlayer_->ApplyDeceleration();

    //�f�o�b�N
    OutputDebugString("IdleState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �E�H�[�N�L�[�������ꂽ��
    if (InputManager::IsWalk()) { pStateManager_->ChangeState("WalkingState"); }
}

void PlayerIdleState::ExitState()
{
}



// ���s���
PlayerWalkingState::PlayerWalkingState(StateManager* manager) : StateBase(manager)
{
}

void PlayerWalkingState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerWalkingState::UpdateState()
{
    //�f�o�b�N
    OutputDebugString("WalkingState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    pPlayer_->Walk();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �_�b�V���L�[�������ꂽ��
    if (InputManager::IsRun()) { pStateManager_->ChangeState("RunningState"); }

    // �ړ����͂��Ȃ��Ȃ����Ƃ��ҋ@��
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerWalkingState::ExitState()
{
}



// ���s���
PlayerRunningState::PlayerRunningState(StateManager* manager) : StateBase(manager)
{
}

void PlayerRunningState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerRunningState::UpdateState()
{
    //�f�o�b�N
    OutputDebugString("RunningState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    pPlayer_->Run();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �ړ����͂��Ȃ��Ȃ����Ƃ��ҋ@��
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerRunningState::ExitState()
{
}



// ������
PlayerJumpingState::PlayerJumpingState(StateManager* manager) : StateBase(manager)
{
}

void PlayerJumpingState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerJumpingState::UpdateState()
{
    //�f�o�b�N
    OutputDebugString("JumpingState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    pPlayer_->Jump();

    // �n�ʂɂ����Ƃ��ҋ@��
    //if (pPlayer->OnGround()) { pStateManager_->ChangeState("IdleState"); }
    //bool OnGround() = getPlayerPos <= 0
}

void PlayerJumpingState::ExitState()
{
}
