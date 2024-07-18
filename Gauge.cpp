#include "Gauge.h"
#include "Engine/Image.h"
#include <cassert>

namespace
{
    // 画像名読み込み
    std::vector<std::string> pictureName =
    {
        "Pictures/HitPoint_Frame.png",
        "Pictures/HitPoint_Green.png",
        "Pictures/HitPoint_Red.png"
    };

    XMFLOAT3 positionOffset = { -0.95f,0.75f,0.0f };
    XMFLOAT3 scaleOffset = { 1.0f, 1.0f, 0.0f };
    const float hpDecreaseSpeed = 1.0f; // HPが減少する速度
}

// コンストラクタ
Gauge::Gauge(GameObject* parent)
    : UIBase(parent, "Gauge"), maxHp_(0), nowHp_(0), targetHp_(0), hpChanged_(true), hpDecreaseSpeed_(hpDecreaseSpeed)
{
}

// デストラクタ
Gauge::~Gauge()
{
}

// 初期化
void Gauge::Initialize()
{
    // 画像読み込み
    hPict_.resize(pictureName.size());
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
    XMFLOAT3 textureSize = Image::GetTextureSize(hPict_[FRAME]);

    // 画像の配置：-1＝左端、0＝中央、1＝右端
    // ウィンドウに合わせる
    transform_.scale_.x = (Direct3D::screenWidth_ / textureSize.x) * scaleOffset.x;
    transform_.scale_.y = scaleOffset.y;  // Y軸のスケールは固定値
}

// HPセッター
void Gauge::SetHp(float maxHp, float nowHp)
{
    maxHp_ = maxHp;
    targetHp_ = nowHp;
    hpChanged_ = true;  // HPが変化したことを示す
}

// 更新
void Gauge::Update()
{
    if (hpChanged_)
    {
        // 現在のHPを目標HPに向かって変化させる
        if (nowHp_ > targetHp_)
        {
            nowHp_ -= hpDecreaseSpeed_;
            if (nowHp_ < targetHp_)
            {
                nowHp_ = targetHp_;
            }
        }
        else if (nowHp_ < targetHp_)
        {
            nowHp_ += hpDecreaseSpeed_;
            if (nowHp_ > targetHp_)
            {
                nowHp_ = targetHp_;
            }
        }

        // HPが変化した場合に描画処理を更新
        if (nowHp_ == targetHp_)
        {
            hpChanged_ = false;  // フラグをリセット
        }
    }
}

// 描画
void Gauge::Draw()
{
    // バーの表示
    Transform transGauge = transform_;
    transGauge.scale_.x *= nowHp_ / maxHp_;

    // 最大HPゲージ
    Image::SetTransform(hPict_[FRAME], transform_);
    Image::Draw(hPict_[FRAME]);

    // 残存HPゲージの画像選択（緑色または赤色）
    int gaugeIndex = (nowHp_ > targetHp_) ? GAUGE_RED : GAUGE_GREEN;

    // 残存HPゲージ
    Image::SetTransform(hPict_[gaugeIndex], transGauge);
    Image::Draw(hPict_[gaugeIndex]);
}

// 開放
void Gauge::Release()
{
}