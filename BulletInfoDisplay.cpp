#include "BulletInfoDisplay.h"
#include "Engine/Image.h"

namespace
{
    XMFLOAT3 MagUiPosition = XMFLOAT3(0.4f, -0.8f, 0.0f);    // 左端の座標
    XMFLOAT3 IconUiPosition = XMFLOAT3(0.2f, -0.8f, 0.0f);   // 弾丸アイコンの座標

    float MagUiBlank = 0.08f;                                // 文字間のサイズ
    XMFLOAT3 MagUiScale = XMFLOAT3(1.0f, 1.0f, 0.0f);        // マガジン画像のサイズ
    XMFLOAT3 IconUiScale = XMFLOAT3(0.2f, 0.2f, 0.0f);       // 弾丸アイコン画像のサイズ
    XMFLOAT3 stateMagUiScale = XMFLOAT3(0.6f, 0.6f, 0.0f);   // マガジン画像のサイズ
    XMFLOAT3 MagCenterUiScale = XMFLOAT3(0.8f, 1.0f, 0.0f);  // マガジン中心画像のサイズ
}

BulletInfoDisplay::BulletInfoDisplay(GameObject* parent)
    : GameObject(parent, "BulletInfoDisplay"), currentMagazine_(0), maxMagazine_(0), missileIconHandle_(-1)
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

    // 弾丸アイコン画像をロード
    missileIconHandle_ = Image::Load("IMG/Missile.png");
    assert(missileIconHandle_ >= 0);
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
    Transform picTrans = transform_;
    picTrans.scale_ = MagUiScale;

    //// 弾丸アイコンの描画 -----------------------
    //Transform iconTrans = transform_;
    //iconTrans.position_ = IconUiPosition;  // 弾丸アイコンの位置
    //iconTrans.scale_ = IconUiScale;        // 弾丸アイコンのサイズ
    //Image::SetTransform(missileIconHandle_, iconTrans);
    //Image::Draw(missileIconHandle_);

    // マガジン残数の表示 ----------------------
    picTrans.position_ = MagUiPosition;

    // 百の位
    if (currentMagazine_ >= 100)    // 100以上の時だけ表示
    {
        int thirdDigit = (currentMagazine_ / 100) % 10;
        Image::SetTransform(hPict_[thirdDigit], picTrans);
        Image::Draw(hPict_[thirdDigit]);
        picTrans.position_.x += MagUiBlank;
    }

    // 十の位
    if (currentMagazine_ >= 10)     // 10以上の時だけ表示
    {
        int secondDigit = (currentMagazine_ / 10) % 10;
        Image::SetTransform(hPict_[secondDigit], picTrans);
        Image::Draw(hPict_[secondDigit]);
        picTrans.position_.x += MagUiBlank;
    }

    // 一の位
    int firstDigit = currentMagazine_ % 10;
    Image::SetTransform(hPict_[firstDigit], picTrans);
    Image::Draw(hPict_[firstDigit]);

    // 中心のスラッシュ画像 -------------------
    picTrans.position_.x += MagUiBlank;
    picTrans.scale_ = MagCenterUiScale;
    Image::SetTransform(hPict_[Slash], picTrans);
    Image::Draw(hPict_[Slash]);

    // 最大マガジンサイズ ----------------------
    picTrans.position_.x += MagUiBlank;

    // 100の位 (maxMagazine_)
    if (maxMagazine_ >= 100)    // 100以上の時だけ表示
    {
        picTrans.scale_ = CalculateFloat3Mul(MagUiScale, stateMagUiScale);
        int thirdDigit = (maxMagazine_ / 100) % 10;
        Image::SetTransform(hPict_[thirdDigit], picTrans);
        Image::Draw(hPict_[thirdDigit]);
        picTrans.position_.x += MagUiBlank * 0.5f;
    }

    // 十の位 (maxMagazine_)
    if (maxMagazine_ >= 10)     // 10以上の時だけ表示
    {
        int secondMaxDigit = (maxMagazine_ / 10) % 10;
        picTrans.scale_ = CalculateFloat3Mul(MagUiScale, stateMagUiScale);
        Image::SetTransform(hPict_[secondMaxDigit], picTrans);
        Image::Draw(hPict_[secondMaxDigit]);
        picTrans.position_.x += MagUiBlank * 0.5f;
    }

    // 一の位 (maxMagazine_)
    int firstMaxDigit = maxMagazine_ % 10;
    picTrans.scale_ = CalculateFloat3Mul(MagUiScale, stateMagUiScale);
    Image::SetTransform(hPict_[firstMaxDigit], picTrans);
    Image::Draw(hPict_[firstMaxDigit]);
}
