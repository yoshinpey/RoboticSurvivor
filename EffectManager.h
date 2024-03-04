#pragma once
#include "Engine/GameObject.h"

class EffectManager : public GameObject
{
public:
    EffectManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
