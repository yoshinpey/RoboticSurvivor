#pragma once
#include "Engine/GameObject.h"

class UIBase : public GameObject
{
public:
    UIBase(GameObject* parent, std::string name)
        :GameObject(parent, name)
    {
    };

    virtual ~UIBase() = default;

    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Release() = 0;
};
