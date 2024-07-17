#pragma once
#include "Engine/GameObject.h"
#include <vector>

class UIManager;

class SceneBase : public GameObject
{
protected:
    std::vector<UIManager*> pUIManagerList_;

public:
    SceneBase(GameObject* parent, std::string name);
    ~SceneBase() override;
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void AddUIManager(UIManager* ma);

    void UIUpdate();
    void UIDraw();

};