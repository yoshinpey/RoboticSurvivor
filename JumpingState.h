#pragma once
#include "StateBase.h"

// ƒWƒƒƒ“ƒvó‘Ô
class JumpingState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
