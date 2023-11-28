#pragma once
#include "StateBase.h"

// ‘–‚èó‘Ô
class RunningState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
