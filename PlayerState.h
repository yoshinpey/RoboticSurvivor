#pragma once
#include "Engine/Text.h"

#include "StateManager.h"
#include "Player.h"
#include "StateBase.h"

// 待機状態
class PlayerIdleState : public StateBase
{
public:
    PlayerIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 歩行状態
class PlayerWalkingState : public StateBase
{
public:
    PlayerWalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 走行状態
class PlayerRunningState : public StateBase
{
public:
    PlayerRunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 跳躍状態
class PlayerJumpingState : public StateBase
{
public:
    PlayerJumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
