#pragma once
#include "Engine/GameObject.h"

class UIBase : public GameObject
{
public:
    XMFLOAT2 position_;
    XMFLOAT2 size_;
    bool visible;

    UIBase(GameObject* parent, std::string name)
        : position_(pos), size_(sz), visible(true) 
    {
    }

    virtual void draw() = 0;
};