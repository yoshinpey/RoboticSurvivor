#pragma once
#include "Engine/GameObject.h"

class EnemyCharacter : public GameObject
{
public:
    EnemyCharacter(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
