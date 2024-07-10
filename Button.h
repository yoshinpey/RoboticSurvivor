#pragma once
#include "Engine/GameObject.h"
#include <functional>

using namespace DirectX;


class UIButton  : public GameObject
{
	// テキスト画像の内容
	enum ButtonState
	{
		NORMAL = 0,		// 何もしていない状態
		HOVER			// カーソルが重なっている状態
	};

	int hPict_[3];					// 画像番号
	int alpha_;						// 透明度
	bool isHovered_;				// ボタンに重なっている
	XMFLOAT2 widePos_;				// 0 ~ 1980とかの座標
	XMFLOAT2 frameSize_;			// 半径
	Transform transform_;

	std::function<void()> onClick_;	// クリックした

public:
	UIButton(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick);
	~UIButton ();

	void Draw();
	bool IsWithinBound();
	void OnClick();

};