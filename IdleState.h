#pragma once
#include "StateBase.h"

// �ҋ@���
class IdleState : public StateBase
{
public:
    
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};