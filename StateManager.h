#pragma once
#include "StateBase.h"

// 状態遷移を管理するクラス
class StateManager
{
private:
    StateBase* currentState_;

public:
    StateManager();
    ~StateManager();

    void Initialize();
    void Update();
    void ChangeState(StateBase* newState);

    void ChangeToIdleState();
    void ChangeToWalkingState();
    void ChangeToRunningState();
    void ChangeToJumpingState();
};
