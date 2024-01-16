#include "PlayerState.h"
#include "StateManager.h"
#include "Player.h"



// 待機状態
PlayerIdleState::PlayerIdleState(StateManager* manager) : StateBase(manager)
{
}

void PlayerIdleState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerIdleState::UpdateState()
{    
    //デバック
    OutputDebugString("IdleState\n");

    // 入力がないときは減速を適用する
    pPlayer_->ApplyDeceleration();

    // ジャンプキーが押されたら
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // ウォークキーが押されたら
    if (InputManager::IsWalk()) { pStateManager_->ChangeState("WalkingState"); }
}

void PlayerIdleState::ExitState()
{
}



// 歩行状態
PlayerWalkingState::PlayerWalkingState(StateManager* manager) : StateBase(manager)
{
}

void PlayerWalkingState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerWalkingState::UpdateState()
{
    //デバック
    OutputDebugString("WalkingState\n");

    pPlayer_->Walk();

    // ジャンプキーが押されたら
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // ダッシュキーが押されたら
    if (InputManager::IsRun()) { pStateManager_->ChangeState("RunningState"); }

    // 移動入力がなくなったとき待機へ
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerWalkingState::ExitState()
{
}



// 走行状態
PlayerRunningState::PlayerRunningState(StateManager* manager) : StateBase(manager)
{
}

void PlayerRunningState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerRunningState::UpdateState()
{
    //デバック
    OutputDebugString("RunningState\n");

    pPlayer_->Run();

    // ジャンプキーが押されたら
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpingState"); }

    // 移動入力がなくなったとき待機へ
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerRunningState::ExitState()
{
}



// 跳躍状態
PlayerJumpingState::PlayerJumpingState(StateManager* manager) : StateBase(manager)
{
}

void PlayerJumpingState::EnterState()
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerJumpingState::UpdateState()
{
    //デバック
    OutputDebugString("JumpingState\n");

    pPlayer_->Jump();

    // 地面についたとき待機へ
    if (pPlayer_->OnGround()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerJumpingState::ExitState()
{
}
