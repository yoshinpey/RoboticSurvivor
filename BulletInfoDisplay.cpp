#include "BulletInfoDisplay.h"
#include "Engine/Image.h"
#include "Gun.h"

namespace
{
    XMFLOAT3 MagUiPosition = XMFLOAT3(0.56f, -0.8f, 0.0f);    // 左端の座標
    XMFLOAT3 MagUiScale = XMFLOAT3(1.0f, 1.0f, 0.0f);        // 装備マガジン画像のサイズ
    XMFLOAT3 stateMagUiScale = XMFLOAT3(0.6f, 0.6f, 0.0f);   // 待機マガジン画像のサイズ
    XMFLOAT3 MagCenterUiScale = XMFLOAT3(0.8f, 1.0f, 0.0f);  // マガジン中心画像のサイズ

    float MagUiBlank = 0.08f;                                // 文字間のサイズ

    XMFLOAT3 IconUiPosition = XMFLOAT3(MagUiPosition.x - 0.12f, MagUiPosition.y, 0.0f);   // 弾丸アイコンの座標
    XMFLOAT3 IconUiScale = XMFLOAT3(0.2f, 0.2f, 0.0f);       // 弾丸アイコン画像のサイズ

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
    std::vector<std::string> paths =
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
        "IMG/Number/Slash.png",
        "IMG/Missile_Unredy.png",
        "IMG/Missile_Redy.png"
    };

    // 画像データのロード
    for (int i = 0; i < paths.size(); ++i)
    {
        int handle = Image::Load(paths[i]);
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
    // 弾丸アイコンの描画 -----------------------
    Transform iconTrans = transform_;
    iconTrans.position_ = IconUiPosition;
    iconTrans.scale_ = IconUiScale;

    // 弾丸の種類に応じて描画するアイコンを変更
    int iconHandle;
    switch (bulletType_)
    {
    case ShootingMode::NORMAL: // 通常弾
        iconHandle = hPict_[Normal];
        break;
    case ShootingMode::EXPLODE: // 爆発弾
        iconHandle = hPict_[Explode];
        break;
    default:
        iconHandle = hPict_[Normal];  // デフォルトは通常弾
        break;
    }
    // 選択されたアイコンを描画
    Image::SetTransform(iconHandle, iconTrans);
    Image::Draw(iconHandle);

    // マガジン残数の表示 ----------------------
    Transform picTrans = transform_;
    picTrans.scale_ = MagUiScale;
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
    picTrans.position_.x += MagUiBlank * 0.5f;
    picTrans.position_.y += MagUiBlank * -0.25f;

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
