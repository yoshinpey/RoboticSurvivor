#pragma once
#include "StageBase.h"

class Player;

class SkyBox : public StageBase
{
    int hModel_;
    Player* pPlayer_;

public:
    SkyBox(GameObject* parent);
    ~SkyBox();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

};

