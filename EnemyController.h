#pragma once
#include "Engine/GameObject.h"

class EnemyController : public GameObject
{
public:
    EnemyController(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
