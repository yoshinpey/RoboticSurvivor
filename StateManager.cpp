#include "StateManager.h"
#include "PlayerState.h"

// コンストラクタ
StateManager::StateManager(GameObject* parent)
    : pParent_(parent), currentState_(nullptr)
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
    PlayerIdleState* idleState = dynamic_cast<PlayerIdleState*>(AddState("IdleState", new PlayerIdleState(this)));
    PlayerWalkingState* walkingState = dynamic_cast<PlayerWalkingState*>(AddState("WalkingState", new PlayerWalkingState(this)));
    PlayerRunningState* runningState = dynamic_cast<PlayerRunningState*>(AddState("RunningState", new PlayerRunningState(this)));
    PlayerJumpingState* jumpingState = dynamic_cast<PlayerJumpingState*>(AddState("JumpingState", new PlayerJumpingState(this)));

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

// 新しい状態を追加
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