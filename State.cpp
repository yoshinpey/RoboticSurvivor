#include "State.h"


// �ҋ@���
void IdleState::EnterState()
{
    pNum = new Text;
    pNum->Initialize();
    // �ҋ@��Ԃɓ���Ƃ��̏���������
}

void IdleState::UpdateState()
{
    pNum->Draw(100, 100, "aaaaaaaaaaaaaaaaa");
    // �ҋ@��Ԃ̍X�V����
}

void IdleState::ExitState()
{
    // �ҋ@��Ԃ���o��Ƃ��̌㏈��
}



// ���s���
void WalkingState::EnterState()
{
    // ���s��Ԃɓ���Ƃ��̏���������
}

void WalkingState::UpdateState()
{
    // ���s��Ԃ̍X�V����
}

void WalkingState::ExitState()
{
    // ���s��Ԃ���o��Ƃ��̌㏈��
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
