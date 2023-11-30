#include "StateManager.h"

// �R���X�g���N�^
StateManager::StateManager(GameObject* gameObj)
{
    gameObj_ = gameObj;
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
    ChangeState(new IdleState(this));
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