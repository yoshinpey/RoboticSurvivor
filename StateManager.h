#pragma once

#include "StateBase.h"

class StateManager
{
private:
    StateBase* currentState_;

public:
    // �R���X�g���N�^
    StateManager();

    // �f�X�g���N�^
    ~StateManager();

    // ��Ԃ̕ύX
    void ChangeState(StateBase* newState);
};
