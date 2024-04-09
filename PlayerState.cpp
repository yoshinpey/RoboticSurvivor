#include "PlayerState.h"
#include "Player.h"
#include "StateManager.h"

// �ҋ@���
PlayerIdleState::PlayerIdleState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerIdleState::EnterState()
{
#ifdef _DEBUG
    // �f�o�b�O�r���h�̎������L��
    OutputDebugString("IdleState\n");
#endif
}

void PlayerIdleState::UpdateState()
{    
    // ���͂��Ȃ��Ƃ��͌�����K�p����
    pPlayer_->ApplyDeceleration();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // �E�H�[�N�L�[�������ꂽ��
    if (InputManager::IsWalk()) { pStateManager_->ChangeState("WalkingState"); }
}

void PlayerIdleState::ExitState()
{
}



// ���s���
PlayerWalkingState::PlayerWalkingState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerWalkingState::EnterState()
{
#ifdef _DEBUG
    OutputDebugString("WalkingState\n");
#endif
}

void PlayerWalkingState::UpdateState()
{

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
PlayerRunningState::PlayerRunningState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerRunningState::EnterState()
{
#ifdef _DEBUG
    OutputDebugString("RunningState\n");
#endif
}

void PlayerRunningState::UpdateState()
{
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
PlayerJumpingState::PlayerJumpingState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerJumpingState::EnterState()
{
#ifdef _DEBUG
    OutputDebugString("JumpingState\n");
#endif
}

void PlayerJumpingState::UpdateState()
{
    pPlayer_->Jump();

    // �n�ʂɂ����Ƃ��ҋ@��
    if (pPlayer_->Jumping()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerJumpingState::ExitState()
{
}
