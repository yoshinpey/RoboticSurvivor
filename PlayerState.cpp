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
    //�f�o�b�N
    OutputDebugString("IdleState\n");

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
    OutputDebugString("WalkingState\n");

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
    OutputDebugString("RunningState\n");

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
    OutputDebugString("JumpingState\n");

    pPlayer_->Jump();

    // �n�ʂɂ����Ƃ��ҋ@��
    if (pPlayer_->OnGround()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerJumpingState::ExitState()
{
}
