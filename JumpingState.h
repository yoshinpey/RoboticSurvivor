#pragma once
#include "StateBase.h"

// �W�����v���
class JumpingState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
