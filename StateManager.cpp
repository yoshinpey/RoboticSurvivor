#include "StateManager.h"

// コンストラクタ
StateManager::StateManager(GameObject* gameObj)
{
    gameObj_ = gameObj;
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
    ChangeState(new IdleState(this));
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