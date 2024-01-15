#include "PlayerState.h"
#include "StateManager.h"
#include "Player.h"

// 待機状態
PlayerIdleState::PlayerIdleState(StateManager* manager) : StateBase(manager)
{
}


void PlayerIdleState::EnterState()
{
}

void PlayerIdleState::UpdateState()
{
    // 入力がないときは移動減速度を適用する
    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->ApplyDeceleration();

    //デバック
    OutputDebugString("IdleState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

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
}

void PlayerWalkingState::UpdateState()
{
    //デバック
    OutputDebugString("WalkingState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Walk();

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
}

void PlayerRunningState::UpdateState()
{
    //デバック
    OutputDebugString("RunningState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Run();

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
}

void PlayerJumpingState::UpdateState()
{
    //デバック
    OutputDebugString("JumpingState");
    float flo = 123.0f;
    OutputDebugStringA(std::to_string(flo).c_str());
    OutputDebugString("\n");

    Player* pPlayer = static_cast<Player*>(pStateManager_->GetGameobject());
    pPlayer->Jump();

    // 地面についたとき待機へ
    //if (pPlayer->OnGround()) { pStateManager_->ChangeState("IdleState"); }
    //bool OnGround() = getPlayerPos <= 0
}

void PlayerJumpingState::ExitState()
{
}
