#pragma once
#include "State.h"

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
};
