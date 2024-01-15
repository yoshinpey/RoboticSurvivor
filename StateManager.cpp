#include "StateManager.h"

// �R���X�g���N�^
StateManager::StateManager(GameObject* gameObj)
    : gameObj_(gameObj), currentState_(nullptr)
{
}

// �f�X�g���N�^
StateManager::~StateManager()
{
    // �v���O�����I�����A��Ԃ��N���[���A�b�v����
    for (const auto& statePair : statesMap_)
    {
        statePair.second->ExitState();
        delete statePair.second;
    }
}

void StateManager::Initialize()
{
    // �C���X�^���X�𐶐����ēo�^
    AddState("IdleState", new IdleState(this));
    AddState("WalkingState", new WalkingState(this));
    AddState("RunningState", new RunningState(this));
    AddState("JumpingState", new JumpingState(this));

    // �������
    ChangeState("IdleState");
}

void StateManager::Update()
{
    if (currentState_ != nullptr)
    {
        currentState_->UpdateState();
    }
}

// ��Ԃ̕ύX
void StateManager::ChangeState(const std::string& stateName)
{
    auto it = statesMap_.find(stateName);

    if (it != statesMap_.end())
    {
        if (currentState_ != nullptr)
        {
            currentState_->ExitState();
        }

        currentState_ = it->second;
        currentState_->EnterState();
    }
}

// �V������Ԃ�ǉ����郁�\�b�h
void StateManager::AddState(const std::string& stateName, StateBase* state)
{
    statesMap_[stateName] = state;
}