#pragma once
#include <functional>
#include "UIBase.h"

class UIButton : public UIBase
{
    // テキスト画像の内容
    enum ButtonPictures
    {
        FRAME_NORMAL = 0,		// 何もしていない状態
        FRAME_HOVER,			// カーソルが重なっている状態
        TEXT,   			    // カーソルが重なっている状態
        MAX                     // 要素数
    };

    std::function<void()> onClick_;                 // クリックしたとき関数を受け取る
    std::array<int, ButtonPictures::MAX> hPict_;    // ボタンの各画像(マウスが重なっている枠、いない枠、テキスト)
    bool isHovered_;                                // ボタンの上にカーソルが重なっているかどうか判定
    int alpha_;						                // 画像透明度(0~255)

    XMFLOAT2 widePos_;				// 0 ~ 1980とかの座標
    XMFLOAT2 frameSize_;			// 画像の一辺の半分
    Transform transform_;

public:

    UIButton(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick);
    ~UIButton();

    virtual void draw() = 0;
    bool checkHover();
};