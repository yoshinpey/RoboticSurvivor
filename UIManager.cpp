#include "UIManager.h"
#include "UIButton.h"
#include "Engine/Input.h"

UIManager::UIManager(SceneBase* parent)
	: state_(UI_STATE::DRAW)
{
}

UIManager::~UIManager()
{
	for (auto u : uiList_)
	{
		delete u;
	}
	uiList_.clear();
}

void UIManager::Update()
{
	for (auto u : uiList_)
	{
		if (u->IsWithinBound()) 
		{
			if (Input::IsMouseButtonUp(0)) 
			{
				u->OnClick();
			}
		}
	}

}

void UIManager::Draw()
{
	for (auto u : uiList_)
	{
		u->Draw();
	}
}

void UIManager::AddUi(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick)
{
	UIBase* ui = new UIButton(name, pos, size, onClick);
	uiList_.push_back(ui);
}