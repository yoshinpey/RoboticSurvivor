#pragma once
#include "StateBase.h"

// ‘Ò‹@ó‘Ô
class IdleState : public StateBase
{
public:
    
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};