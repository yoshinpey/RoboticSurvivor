#pragma once
#include "Character.h"

// マルチに対応したら意味が出るかも知れない程度の無意味クラス
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
