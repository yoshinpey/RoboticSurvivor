#pragma once
#include "StateBase.h"

// ������
class RunningState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
