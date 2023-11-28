#pragma once
#include "State.h"

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
};
