#include "PlayerState.h"
#include "Player.h"
#include "StateManager.h"

// 待機状態
PlayerIdleState::PlayerIdleState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerIdleState::EnterState()
{
#ifdef _DEBUG
    // デバッグビルドの時だけ有効
    OutputDebugString("IdleState\n");
#endif
}

void PlayerIdleState::UpdateState()
{    
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
PlayerWalkingState::PlayerWalkingState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerWalkingState::EnterState()
{
#ifdef _DEBUG
    OutputDebugString("WalkingState\n");
#endif
}

void PlayerWalkingState::UpdateState()
{

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
PlayerRunningState::PlayerRunningState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerRunningState::EnterState()
{
#ifdef _DEBUG
    OutputDebugString("RunningState\n");
#endif
}

void PlayerRunningState::UpdateState()
{
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
PlayerJumpingState::PlayerJumpingState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr)
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameobject());
}

void PlayerJumpingState::EnterState()
{
#ifdef _DEBUG
    OutputDebugString("JumpingState\n");
#endif
}

void PlayerJumpingState::UpdateState()
{
    pPlayer_->Jump();

    // 地面についたとき待機へ
    if (pPlayer_->Jumping()) { pStateManager_->ChangeState("IdleState"); }
}

void PlayerJumpingState::ExitState()
{
}
