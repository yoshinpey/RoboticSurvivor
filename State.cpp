#include "State.h"
#include "Player.h"
#include "StateManager.h"

IdleState::IdleState(StateManager* manager) : StateBase(manager)
{
}

// 待機状態
void IdleState::EnterState()
{
    pNum = new Text;
    pNum->Initialize();
    // 待機状態に入るときの初期化処理
}

void IdleState::UpdateState()
{
    
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->testDRW = true;
    // 待機状態の更新処理
}

void IdleState::ExitState()
{
    // 待機状態から出るときの後処理
}



WalkingState::WalkingState(StateManager* manager) : StateBase(manager)
{
}

// 歩行状態
void WalkingState::EnterState()
{
    // 歩行状態に入るときの初期化処理
}

void WalkingState::UpdateState()
{
    // 歩行状態の更新処理
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->testDRW = false;
}

void WalkingState::ExitState()
{
    // 歩行状態から出るときの後処理
}



RunningState::RunningState(StateManager* manager) : StateBase(manager)
{
}

// 走行状態
void RunningState::EnterState()
{
    // 走行状態に入るときの初期化処理
}

void RunningState::UpdateState()
{
    // 走行状態の更新処理
}

void RunningState::ExitState()
{
    // 走行状態から出るときの後処理
}



JumpingState::JumpingState(StateManager* manager) : StateBase(manager)
{
}

// 跳躍状態
void JumpingState::EnterState()
{
    // 跳躍状態に入るときの初期化処理
}

void JumpingState::UpdateState()
{
    // 跳躍状態の更新処理
}

void JumpingState::ExitState()
{
    // 跳躍状態から出るときの後処理
}
