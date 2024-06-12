#pragma once
#include "StageBase.h"

class Player;

class Stage_Skybox : public StageBase
{
    int hModel_;
    Player* pPlayer_;

public:
    Stage_Skybox(GameObject* parent);
    ~Stage_Skybox();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

};

