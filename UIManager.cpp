#include "UIManager.h"
#include "UIButton.h"
#include "Engine/Input.h"

UIManager::UIManager(SceneBase* parent)
    : state_(UI_STATE::DRAW)
{
}

UIManager::~UIManager()
{
    // unique_ptrが自動的にメモリを解放するため、明示的なdeleteは不要
}

void UIManager::Update()
{
    for (const auto& u : uiList_)
    {
        // UIButton型にキャスト
        UIButton* button = dynamic_cast<UIButton*>(u.get());
        if (button && button->CheckingHover())
        {
            if (Input::IsMouseButtonUp(0))
            {
                button->OnClick();
            }
        }
    }
}

void UIManager::Draw()
{
    for (const auto& u : uiList_)
    {
        u->Draw();
    }
}

void UIManager::AddUi(const std::string& name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick)
{
    uiList_.emplace_back(std::make_unique<UIButton>(name, pos, size, onClick));
}
