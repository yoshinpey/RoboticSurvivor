#pragma once
#include "StateBase.h"

// ジャンプ状態
class JumpingState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
