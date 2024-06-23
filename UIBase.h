#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <string>

// UIベースクラス
class UIBase : public GameObject
{
public:
    UIBase(GameObject* parent, const std::string& name)
        : GameObject(parent, name) 
    {
    }
    virtual ~UIBase() = default;

    virtual void Initialize() override = 0;
    virtual void Update() override = 0;
    virtual void Draw() override = 0;
    virtual void Release() override = 0;
};