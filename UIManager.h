#pragma once
#include <vector>
#include <string>
#include <DirectXMath.h>
#include<functional>

using namespace DirectX;
class UIBase;

class UIManager
{
public:
	enum UI_STATE {
		DRAW = 0,
		ENDDRAW,
	};

protected:
	std::vector<UIBase*> uiList_;
	UI_STATE state_;

public:
	UIManager();
	virtual ~UIManager();
	virtual void Update();
	virtual void Draw();

	//�{�^���̒ǉ�
	void AddUi(std::string name, XMFLOAT2 pos, std::function<void()> onClick);
	//�{�^���̒ǉ�
	void AddUi(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick);

	UI_STATE GetUIState() { return state_; };

};