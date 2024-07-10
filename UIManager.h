#pragma once
#include <vector>
#include <string>
#include <DirectXMath.h>
#include <functional>
#include <memory>
#include "SceneBase.h"

using namespace DirectX;
class UIBase;

class UIManager
{
public:
    enum UI_STATE
    {
        DRAW = 0,
        ENDDRAW,
    };

protected:
    std::vector<std::unique_ptr<UIBase>> uiList_;
    UI_STATE state_;

public:
    UIManager(SceneBase* parent);
    virtual ~UIManager();
    virtual void Update();
    virtual void Draw();

    //ƒ{ƒ^ƒ“‚Ì’Ç‰Á
    void AddUi(const std::string& name, XMFLOAT2 pos, XMFLOAT2 size = { 1.0f, 1.0f }, std::function<void()> onClick);

    UI_STATE GetUIState() const { return state_; };
};
