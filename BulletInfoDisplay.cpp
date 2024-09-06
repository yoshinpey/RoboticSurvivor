// BulletInfoDisplay.cpp
#include "BulletInfoDisplay.h"
#include "Engine/Image.h"

namespace 
{
    XMFLOAT3 MagUiPosition = XMFLOAT3(0.4f, -0.8f, 0.0f);    //左端の座標

    float MagUiBlank = 0.08f;                             //文字間のサイズ
    XMFLOAT3 MagUiScale = XMFLOAT3(1.0f, 1.0f, 1.0f);        //マガジン画像のサイズ
    XMFLOAT3 MagCenterUiScale = XMFLOAT3(0.6f, 0.25f, 1.0f); //マガジン中心画像のサイズ
}

BulletInfoDisplay::BulletInfoDisplay(GameObject* parent)
    : GameObject(parent, "BulletInfoDisplay"), currentMagazine_(0), maxMagazine_(0)
{
}

BulletInfoDisplay::~BulletInfoDisplay()
{
}

void BulletInfoDisplay::Initialize()
{
    // 画像のパス
    std::vector<std::string> numPicturePaths =
    {
        "IMG/Number/0.png",
        "IMG/Number/1.png",
        "IMG/Number/2.png",
        "IMG/Number/3.png",
        "IMG/Number/4.png",
        "IMG/Number/5.png",
        "IMG/Number/6.png",
        "IMG/Number/7.png",
        "IMG/Number/8.png",
        "IMG/Number/9.png",
        "IMG/Number/Slash.png"
    };

    // 画像データのロード
    for (int i = 0; i < numPicturePaths.size(); ++i)
    {
        int handle = Image::Load(numPicturePaths[i]);
        assert(handle >= 0);
        hPict_.push_back(handle);
    }
}

void BulletInfoDisplay::Update()
{
}

void BulletInfoDisplay::Draw()
{
}

void BulletInfoDisplay::Release()
{
}

void BulletInfoDisplay::DrawBullet()
{
    //十の位
    Transform picTrans = transform_;
    picTrans.position_ = MagUiPosition;
    picTrans.scale_ = MagUiScale;
    int secondDigit = (currentMagazine_ / 10) % 10;
    Image::SetTransform(hPict_[secondDigit], picTrans);
    Image::Draw(hPict_[secondDigit]);

    //一の位
    picTrans.position_.x += MagUiBlank;
    int firstDigit = currentMagazine_ % 10;
    Image::SetTransform(hPict_[firstDigit], picTrans);
    Image::Draw(hPict_[firstDigit]);

    //中心の画像-------------------
    picTrans.position_.x += MagUiBlank;
    picTrans.scale_ = MagCenterUiScale;
    Image::SetTransform(hPict_[9 + CENTER + 1], picTrans);
    Image::Draw(hPict_[9 + CENTER + 1]);

    //最大マガジンサイズ----------------------
    //十の位
    picTrans.position_.x += MagUiBlank;
    picTrans.scale_ = MagUiScale;
    secondDigit = (maxMagazine_ / 10) % 10;
    Image::SetTransform(hPict_[secondDigit], picTrans);
    Image::Draw(hPict_[secondDigit]);

    //一の位
    firstDigit = maxMagazine_ % 10;
    picTrans.position_.x += MagUiBlank;
    Image::SetTransform(hPict_[firstDigit], picTrans);
    Image::Draw(hPict_[firstDigit]);
}