#include "StateManager.h"

#include "IdleState.h"
#include "WalkingState.h"
#include "RunningState.h"
#include "JumpingState.h"

// コンストラクタ
StateManager::StateManager() : currentState_(nullptr) 
{
}

// デストラクタ
StateManager::~StateManager()
{
    // プログラム終了時、状態をクリーンアップする
    if (currentState_ != nullptr)
    {
        currentState_->ExitState();
        delete currentState_;
        currentState_ = nullptr;
    }
}

void StateManager::Initialize()
{
    // 初期状態
    ChangeToIdleState();
}

void StateManager::Update()
{
    if (currentState_ != nullptr)
    {
        currentState_->UpdateState();
    }
}

// 状態の変更
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