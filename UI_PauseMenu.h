#pragma once
#include "UIManager.h"

class UI_PauseMenu : public UIManager
{
public:
	UI_PauseMenu(SceneBase* parent);
	~UI_PauseMenu();
	void Draw() override;
};