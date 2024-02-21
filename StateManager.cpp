#include "StateManager.h"
#include "PlayerState.h"

// �R���X�g���N�^
StateManager::StateManager(GameObject* parent)
    : pParent_(parent), currentState_(nullptr)
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
    // ���炩���ߏ�ԃC���X�^���X�𐶐����ēo�^
    PlayerIdleState* idleState = dynamic_cast<PlayerIdleState*>(AddState("IdleState", new PlayerIdleState(this)));
    PlayerWalkingState* walkingState = dynamic_cast<PlayerWalkingState*>(AddState("WalkingState", new PlayerWalkingState(this)));
    PlayerRunningState* runningState = dynamic_cast<PlayerRunningState*>(AddState("RunningState", new PlayerRunningState(this)));
    PlayerJumpingState* jumpingState = dynamic_cast<PlayerJumpingState*>(AddState("JumpingState", new PlayerJumpingState(this)));

    // �e��Ԃ̏�����
    if (idleState != nullptr) idleState->EnterState();
    if (walkingState != nullptr) walkingState->EnterState();
    if (runningState != nullptr) runningState->EnterState();
    if (jumpingState != nullptr) jumpingState->EnterState();

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

// �V������Ԃ�ǉ�
StateBase* StateManager::AddState(const std::string& stateName, StateBase* state)
{
    auto it = statesMap_.find(stateName);

    if (it != statesMap_.end())
    {
        // ���ɓ������O�̏�Ԃ����݂���ꍇ�͂��̃|�C���^��Ԃ�
        return it->second;
    }

    // ���݂��Ȃ��ꍇ�͐V������Ԃ�o�^
    statesMap_[stateName] = state;
    return state;
}