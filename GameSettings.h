#pragma once
#include "Engine/GameObject.h"

class GameSettings : public GameObject
{
public:
    GameSettings(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
