#pragma once
#include "StateBase.h"

class Player;

// �ҋ@���
class PlayerIdleState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class PlayerWalkingState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerWalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class PlayerRunningState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerRunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ������
class PlayerJumpingState : public StateBase
{
    Player* pPlayer_;
public:
    PlayerJumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
