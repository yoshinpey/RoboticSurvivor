#pragma once
#include "UIManager.h"

class UIMenu : public UIManager
{
public:
	UIMenu(SceneBase* parent);
	~UIMenu() override;
	void Draw() override;
};