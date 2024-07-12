#include "UIMenu.h"
#include "AudioManager.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

namespace 
{
}

UIMenu::UIMenu(SceneBase* parent)
	: UIManager(parent)
{
	//SceneManager* pSceneManager_ = (SceneManager*)FindObject("SceneManager");
	AddUi("Start", { 0.0f, 0.0f }, { 1.0f, 1.0f }, [this]()
		{
			// ボタンがクリックされたときの処理
			OutputDebugString("pressed\n");
		});
}

UIMenu::~UIMenu()
{
}

void UIMenu::Draw()
{
	UIManager::Draw();
}