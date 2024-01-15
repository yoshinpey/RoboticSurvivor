#pragma once
#include "Engine/Text.h"

#include "StateManager.h"
#include "Player.h"
#include "StateBase.h"

// ‘Ò‹@ó‘Ô
class PlayerIdleState : public StateBase
{
public:
    PlayerIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// •àsó‘Ô
class PlayerWalkingState : public StateBase
{
public:
    PlayerWalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ‘–só‘Ô
class PlayerRunningState : public StateBase
{
public:
    PlayerRunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ’µ–ôó‘Ô
class PlayerJumpingState : public StateBase
{
public:
    PlayerJumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
