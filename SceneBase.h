#pragma once
#include "Engine/GameObject.h"
#include <vector>

class UIManager;

class SceneBase : public GameObject
{
public:
    SceneBase(GameObject* parent, std::string name);
    ~SceneBase();
};