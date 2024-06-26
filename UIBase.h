#pragma once
#include <DirectXMath.h>
#include <string>
#include <functional>
#include "Engine/Transform.h"

using namespace DirectX;

class UIBase
{
	int hPict_[3];
	int alpha_;
	bool isBound_;			//�͈͂̓����ɂ��邩�ǂ���
	XMFLOAT2 widePos_;		//0 ~ 1980�Ƃ��̍��W
	XMFLOAT2 frameSize_;	//���a
	Transform transform_;

	enum BUTTON_STATE 
	{
		POINT = 0,
		ENTER,
	};

	std::function<void()> onClick_;

public:
	UIBase();
	~UIBase();
	void Initialize(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick);
	void Draw();
	bool IsWithinBound();
	void OnClick();

};