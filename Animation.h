#pragma once
#include "Engine/GameObject.h"

class Animation : public GameObject
{
public:
    Animation(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
