#pragma once
#include "StateBase.h"

// ó‘Ô‘JˆÚ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
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
