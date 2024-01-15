#pragma once
#include "Engine/Text.h"

#include "StateManager.h"
#include "Player.h"
#include "StateBase.h"

// �ҋ@���
class PlayerIdleState : public StateBase
{
public:
    PlayerIdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class PlayerWalkingState : public StateBase
{
public:
    PlayerWalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ���s���
class PlayerRunningState : public StateBase
{
public:
    PlayerRunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// ������
class PlayerJumpingState : public StateBase
{
public:
    PlayerJumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
