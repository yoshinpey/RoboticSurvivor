#pragma once
#include "StateBase.h"

class Player;

// ‘Ò‹@ó‘Ô
class PlayerIdleState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// •àsó‘Ô
class PlayerWalkingState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerWalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ‘–só‘Ô
class PlayerRunningState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerRunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ’µ–ôó‘Ô
class PlayerJumpingState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerJumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
