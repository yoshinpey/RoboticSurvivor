#include "State.h"
#include "Player.h"
#include "StateManager.h"

IdleState::IdleState(StateManager* manager) : StateBase(manager)
{
}

// �ҋ@���
void IdleState::EnterState()
{
    pNum = new Text;
    pNum->Initialize();
    // �ҋ@��Ԃɓ���Ƃ��̏���������
}

void IdleState::UpdateState()
{
    
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->testDRW = true;
    // �ҋ@��Ԃ̍X�V����
}

void IdleState::ExitState()
{
    // �ҋ@��Ԃ���o��Ƃ��̌㏈��
}



WalkingState::WalkingState(StateManager* manager) : StateBase(manager)
{
}

// ���s���
void WalkingState::EnterState()
{
    // ���s��Ԃɓ���Ƃ��̏���������
}

void WalkingState::UpdateState()
{
    // ���s��Ԃ̍X�V����
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->testDRW = false;
}

void WalkingState::ExitState()
{
    // ���s��Ԃ���o��Ƃ��̌㏈��
}



RunningState::RunningState(StateManager* manager) : StateBase(manager)
{
}

// ���s���
void RunningState::EnterState()
{
    // ���s��Ԃɓ���Ƃ��̏���������
}

void RunningState::UpdateState()
{
    // ���s��Ԃ̍X�V����
}

void RunningState::ExitState()
{
    // ���s��Ԃ���o��Ƃ��̌㏈��
}



JumpingState::JumpingState(StateManager* manager) : StateBase(manager)
{
}

// ������
void JumpingState::EnterState()
{
    // �����Ԃɓ���Ƃ��̏���������
}

void JumpingState::UpdateState()
{
    // �����Ԃ̍X�V����
}

void JumpingState::ExitState()
{
    // �����Ԃ���o��Ƃ��̌㏈��
}
