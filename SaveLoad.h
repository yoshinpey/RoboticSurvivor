#pragma once
#include "Engine/GameObject.h"

class SaveLoad : public GameObject
{
public:
    SaveLoad(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
