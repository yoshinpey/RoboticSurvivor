#pragma once
#include "Engine/GameObject.h"

// e’e‚ÌŠî’êƒNƒ‰ƒX
class BulletBase : public GameObject
{
public:
    BulletBase(GameObject* parent, std::string name)
        :GameObject(parent, name)
    {
    };

    virtual ~BulletBase()
    {
    };

    struct BulletParameter
    {
        float killTimer_;
        float speed_;
        float damage_;
        float shotCoolTime_;
    };
};