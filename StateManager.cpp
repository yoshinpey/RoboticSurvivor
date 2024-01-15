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
    // あらかじめ状態インスタンスを生成して登録
    IdleState* idleState = dynamic_cast<IdleState*>(AddState("IdleState", new IdleState(this)));
    WalkingState* walkingState = dynamic_cast<WalkingState*>(AddState("WalkingState", new WalkingState(this)));
    RunningState* runningState = dynamic_cast<RunningState*>(AddState("RunningState", new RunningState(this)));
    JumpingState* jumpingState = dynamic_cast<JumpingState*>(AddState("JumpingState", new JumpingState(this)));

    // 各状態の初期化
    if (idleState != nullptr) idleState->EnterState();
    if (walkingState != nullptr) walkingState->EnterState();
    if (runningState != nullptr) runningState->EnterState();
    if (jumpingState != nullptr) jumpingState->EnterState();

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

// 新しい状態を追加（既に同じ名前の状態が存在すればそのポインタを返す）
StateBase* StateManager::AddState(const std::string& stateName, StateBase* state)
{
    auto it = statesMap_.find(stateName);

    if (it != statesMap_.end())
    {
        // 既に同じ名前の状態が存在する場合はそのポインタを返す
        return it->second;
    }

    // 存在しない場合は新しい状態を登録
    statesMap_[stateName] = state;
    return state;
}