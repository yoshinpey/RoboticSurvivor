#pragma once
#include "Character.h"

class PlayerBase : public Character
{
public:
    PlayerBase(GameObject* parent, std::string name)
        : Character(parent, name)
    {
    }

    virtual ~PlayerBase()
    {
    };
};
