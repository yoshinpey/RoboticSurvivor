#pragma once
#include "Engine/Text.h"

class StateManager;

// ��ԃx�[�X�N���X
class StateBase
{   
protected:
    Text* pNum;                 // �e�L�X�g
    StateManager* pStateManager_;
public:
    StateBase(StateManager* manager) : pStateManager_(manager) {}

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
    IdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class WalkingState : public StateBase
{
public:
    WalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class RunningState : public StateBase
{
public:
    RunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ������
class JumpingState : public StateBase
{
public:
    JumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
