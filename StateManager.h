#pragma once

#include "StateBase.h"

class StateManager
{
private:
    StateBase* currentState_;

public:
    // コンストラクタ
    StateManager();

    // デストラクタ
    ~StateManager();

    // 状態の変更
    void ChangeState(StateBase* newState);
};
