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
	AddUi("Start", XMFLOAT2(0.0f, -0.5f), XMFLOAT2(0.0f, -0.5f), [this]() {PostQuitMessage(0); });
	
}

UIMenu::~UIMenu()
{
}

void UIMenu::Draw()
{
	UIManager::Draw();
}