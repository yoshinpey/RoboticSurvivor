#pragma once
#include "EnemyCharacter.h"

class EnemyType : public EnemyCharacter
{
public:
    EnemyType(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
