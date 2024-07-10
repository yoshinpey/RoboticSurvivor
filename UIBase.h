#pragma once
#include <array>
#include <string>
#include <DirectXMath.h>

using namespace DirectX;

class UIBase 
{
public:
    std::string name_;          // UIの名前
    XMFLOAT2 position_;         // UIの位置
    XMFLOAT2 size_;             // UIのサイズ

    UIBase(std::string name, XMFLOAT2 pos, XMFLOAT2 size);
    virtual ~UIBase();

    virtual void draw() = 0;
};