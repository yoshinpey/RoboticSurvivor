#include "StateManager.h"

#include "IdleState.h"
#include "WalkingState.h"
#include "RunningState.h"
#include "JumpingState.h"

// �R���X�g���N�^
StateManager::StateManager() : currentState_(nullptr) 
{
}

// �f�X�g���N�^
StateManager::~StateManager()
{
    // �v���O�����I�����A��Ԃ��N���[���A�b�v����
    if (currentState_ != nullptr)
    {
        currentState_->ExitState();
        delete currentState_;
        currentState_ = nullptr;
    }
}

void StateManager::Initialize()
{
    // �������
    ChangeToIdleState();
}

void StateManager::Update()
{
    if (currentState_ != nullptr)
    {
        currentState_->UpdateState();
    }
}

// ��Ԃ̕ύX
void StateManager::ChangeState(StateBase* newState)
{
    if (currentState_ != nullptr)
    {
        currentState_->ExitState();
        delete currentState_;
    }

    currentState_ = newState;
    currentState_->EnterState();
}

void StateManager::ChangeToIdleState()
{
    ChangeState(new IdleState());
}

void StateManager::ChangeToWalkingState()
{
    ChangeState(new WalkingState());
}

void StateManager::ChangeToRunningState()
{
    ChangeState(new RunningState());
}

void StateManager::ChangeToJumpingState()
{
    ChangeState(new JumpingState());
}