#pragma once
#include "StateBase.h"
#include "Player.h"

// 歩き状態
class WalkingState : public StateBase
{
private:
    Player* player_;

public:
    // コンストラクタ
    WalkingState(Player* player);

    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};