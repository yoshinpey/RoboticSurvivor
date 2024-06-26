#pragma once
#include "StateBase.h"

class Player;

// 待機状態
class PlayerIdleState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 歩行状態
class PlayerWalkingState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerWalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 走行状態
class PlayerRunningState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerRunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 跳躍状態
class PlayerJumpingState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerJumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
