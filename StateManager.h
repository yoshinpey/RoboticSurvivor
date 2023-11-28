#pragma once
#include "StateBase.h"

// ��ԑJ�ڂ��Ǘ�����N���X
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
