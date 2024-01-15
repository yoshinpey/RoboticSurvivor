#include "StateManager.h"

// コンストラクタ
StateManager::StateManager(GameObject* gameObj)
    : gameObj_(gameObj), currentState_(nullptr)
{
}

// デストラクタ
StateManager::~StateManager()
{
    // プログラム終了時、状態をクリーンアップする
    for (const auto& statePair : statesMap_)
    {
        statePair.second->ExitState();
        delete statePair.second;
    }
}

void StateManager::Initialize()
{
    // インスタンスを生成して登録
    AddState("IdleState", new IdleState(this));
    AddState("WalkingState", new WalkingState(this));
    AddState("RunningState", new RunningState(this));
    AddState("JumpingState", new JumpingState(this));

    // 初期状態
    ChangeState("IdleState");
}

void StateManager::Update()
{
    if (currentState_ != nullptr)
    {
        currentState_->UpdateState();
    }
}

// 状態の変更
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

// 新しい状態を追加するメソッド
void StateManager::AddState(const std::string& stateName, StateBase* state)
{
    statesMap_[stateName] = state;
}