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
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());

    // 方向計算
    pPlayer->CalculateMoveInput();

    // ジャンプキーが押されたらジャンプ状態に遷移
    if (InputManager::IsJump())
    {
        pStateManager_->ChangeState(new JumpingState(pStateManager_));
    }

    pPlayer->Move();

    // 加速を適用
    pPlayer->CalculateMoveInput();


    // ジャンプキーが押されたらジャンプ状態に遷移
    if (InputManager::IsJump())
    {
        pStateManager_->ChangeState(new JumpingState(pStateManager_));
    }
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

    // ジャンプキーが押されたらジャンプ状態に遷移
    if (InputManager::IsJump())
    {
        pStateManager_->ChangeState(new JumpingState(pStateManager_));
    }
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
}

void JumpingState::ExitState()
{
}
