#pragma once
#include "Engine/GameObject.h"

class MiniMap : public GameObject
{
public:
    MiniMap(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
