#include "StateManager.h"

// �R���X�g���N�^
StateManager::StateManager() : currentState_(nullptr) 
{
}

// �f�X�g���N�^
StateManager::~StateManager()
{
    // �v���O�����I������StateManager���j�������ہA���݂̏�Ԃ��N���[���A�b�v����
    if (currentState_ != nullptr)
    {
        currentState_->ExitState();
        delete currentState_;
        currentState_ = nullptr;
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