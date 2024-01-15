#include "State.h"
#include "Player.h"
#include "StateManager.h"


// 待機状態
IdleState::IdleState(StateManager* manager) : StateBase(manager)
{
}

void IdleState::EnterState()
{
}

void IdleState::UpdateState()
{

    // ジャンプキーが押されたら
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // ウォークキーが押されたら
    if (InputManager::IsRun()) { pStateManager_->ChangeState("WalkingState"); }
}

void IdleState::ExitState()
{
}


// 歩行状態
WalkingState::WalkingState(StateManager* manager) : StateBase(manager)
{
}

void WalkingState::EnterState()
{
}

void WalkingState::UpdateState()
{   
    OutputDebugString("aaa");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->CalculateMoveInput();
    pPlayer->Walk();

    // ジャンプキーが押されたら
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // ダッシュキーが押されたら
    if (InputManager::IsRun()) { pStateManager_->ChangeState("RunningState"); }
}

void WalkingState::ExitState()
{
}


// 走行状態
RunningState::RunningState(StateManager* manager) : StateBase(manager)
{
}

void RunningState::EnterState()
{
}

void RunningState::UpdateState()
{
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->CalculateMoveInput();
    pPlayer->Walk();

    // ジャンプキーが押されたら
    if (InputManager::IsJump()){pStateManager_->ChangeState("RunningState");}
}

void RunningState::ExitState()
{
}


// 跳躍状態
JumpingState::JumpingState(StateManager* manager) : StateBase(manager)
{
}

void JumpingState::EnterState()
{
}

void JumpingState::UpdateState()
{
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Jump();
}

void JumpingState::ExitState()
{
}
