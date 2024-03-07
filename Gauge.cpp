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
    :GameObject(parent, "Gauge"), hpPict_{ -1,-1 },maxHp_(0),nowHp_(0)
{
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
        hpPict_[i] = Image::Load(pictureName[i]);
        assert(hpPict_[i] >= 0);
    }

    // 位置調整
    transform_.position_ = positionOffset;
    // サイズ調整
    transform_.scale_ = scaleOffset;
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
    transGauge.scale_.x = nowHp_ / maxHp_;

    // 最大HPゲージ
    Image::SetTransform(hpPict_[0], transform_);
    Image::Draw(hpPict_[0]);
    // 残存HPゲージ
    Image::SetTransform(hpPict_[1], transGauge);
    Image::Draw(hpPict_[1]);


}

//開放
void Gauge::Release()
{
}