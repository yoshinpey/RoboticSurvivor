#include "Engine/Image.h"
#include "Gauge.h"

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
    //中身
    hpPict_[0] = Image::Load("HitPoint.png");
    assert(hpPict_[0] >= 0);
    //枠
    hpPict_[1] = Image::Load("HitPointFrame.png");
    assert(hpPict_[1] >= 0);

    //位置調整
    transform_.position_.x = -0.95;
    transform_.position_.y = 0.75;
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
    transGauge.scale_.x = (float)nowHp_ / (float)maxHp_;

    Image::SetTransform(hpPict_[0], transGauge);
    Image::Draw(hpPict_[0]);

    Image::SetTransform(hpPict_[1], transform_);
    Image::Draw(hpPict_[1]);
}

//開放
void Gauge::Release()
{
}