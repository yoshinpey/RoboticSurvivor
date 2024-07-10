#pragma once
#include <functional>
#include "UIBase.h"


class UIButton : public UIBase
{
    // テキスト画像の内容
    enum ButtonState
    {
        NORMAL = 0,		// 何もしていない状態
        HOVER			// カーソルが重なっている状態
    };

    std::function<void()> onClick_;     // クリックしたとき関数を受け取る
    std::array<int, 2> hButtonPict_;    // ボタンフレームの各状態画像(マウスが重なっている、いない)
    int hTextPict_;                     // ボタンに表示する文字画像
    bool isHovered_;                    // ボタンの上にカーソルが重なっているかどうか判定
    int alpha_;						    // 画像透明度(0~255)

    XMFLOAT2 widePos_;				// 0 ~ 1980とかの座標
    XMFLOAT2 frameSize_;			// 半径
    Transform transform_;

public:

    UIButton(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick);
    ~UIButton();

    virtual void draw() = 0;
    bool checkHover(XMFLOAT2 cursorPosition);
};