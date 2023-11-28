#pragma once

// ��ԃx�[�X�N���X
class StateBase
{
public:
    // �f�X�g���N�^
    virtual ~StateBase() {};
    // ��Ԃɓ���Ƃ��̏�����
    virtual void EnterState() = 0;
    // ��Ԃ̍X�V
    virtual void UpdateState() = 0;
    // ��Ԃ���o��Ƃ��̌㏈��
    virtual void ExitState() = 0;
};

// �ҋ@���
class IdleState : public StateBase
{
public:

    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class WalkingState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class RunningState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ������
class JumpingState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
