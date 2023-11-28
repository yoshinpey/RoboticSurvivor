#pragma once
#include "StateBase.h"
#include "Player.h"

// �������
class WalkingState : public StateBase
{
private:
    Player* player_;

public:
    // �R���X�g���N�^
    WalkingState(Player* player);

    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};