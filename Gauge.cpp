#include "Engine/Image.h"
#include "Gauge.h"

namespace
{
    // 画像名読み込み
    std::vector<std::string> pictureName =
    {
        "Pictures/HitPoint_longFrame.png",
        "Pictures/HitPoint_long.png"
    };

    XMFLOAT3 positionOffset = { -0.95f,0.75f,0.0f };
    XMFLOAT3 scaleOffset = { 1.0f, 1.0f, 0.0f };
}

//コンストラクタ
Gauge::Gauge(GameObject* parent)
    :UIBase(parent, "Gauge"), maxHp_(0), nowHp_(0)
{
    // 画像読み込み
    hPict_.resize(pictureName.size());
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
    // 画像読み込み
    for (int i = 0; i < pictureName.size(); ++i)
    {
        hPict_[i] = Image::Load(pictureName[i]);
        assert(hPict_[i] >= 0);
    }

    // 位置調整
    transform_.position_ = positionOffset;
    // サイズ調整
    transform_.scale_ = scaleOffset;

    // ゲージフレーム画像のサイズ取得
    XMFLOAT3 size = Image::GetTextureSize(hPict_[FRAME]);

    // 画像の配置：-1＝左端、0＝中央、1＝右端
    // ウィンドウに合わせる
    transform_.scale_.x = (Direct3D::screenWidth_ / size.x) * scaleOffset.x;
    transform_.scale_.y = scaleOffset.y;                                        // Y軸のスケールは固定値
}

//更新
void Gauge::Update()
{
}

//描画
void Gauge::Draw()
{
    //バーの表示
    Transform transGauge = transform_;
    transGauge.scale_.x *= nowHp_ / maxHp_;

    // 最大HPゲージ
    Image::SetTransform(hPict_[FRAME], transform_);
    Image::Draw(hPict_[FRAME]);

    // 残存HPゲージ
    Image::SetTransform(hPict_[GAUGE], transGauge);
    Image::Draw(hPict_[GAUGE]);
}

//開放
void Gauge::Release()
{
}