#include "StateManager.h"

// コンストラクタ
StateManager::StateManager() : currentState_(nullptr) 
{
}

// デストラクタ
StateManager::~StateManager()
{
    // プログラム終了時にStateManagerが破棄される際、現在の状態をクリーンアップする
    if (currentState_ != nullptr)
    {
        currentState_->ExitState();
        delete currentState_;
        currentState_ = nullptr;
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