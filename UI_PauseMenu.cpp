#include "UI_PauseMenu.h"
#include "AudioManager.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

namespace 
{
}

UI_PauseMenu::UI_PauseMenu(SceneBase* parent)
	: UIManager(parent)
{
	//SceneManager* pSceneManager_ = (SceneManager*)FindObject("SceneManager");
	AddUi("Start", { 0.0f, 0.0f }, { 1.0f, 1.0f }, [this]()
		{
			// ボタンがクリックされたときの処理
			OutputDebugString("pressed\n");
		});
}

UI_PauseMenu::~UI_PauseMenu()
{
}

void UI_PauseMenu::Draw()
{
	UIManager::Draw();
}