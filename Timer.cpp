#include "Timer.h"
#include "Engine/Text.h"

namespace
{
    XMINT2 position = { 10,20 };
    int offsetX = 100;
    float defaultScale = 1.0f;
    int movingFlame = 10;
    float changeRate = 0.2f;
}

//コンストラクタ
Timer::Timer(GameObject* parent)
    :GameObject(parent, "Timer"), pNum_(nullptr), frame_(0), active_(false)
{
    pNum_ = new Text;
}

//デストラクタ
Timer::~Timer()
{
}

//初期化
void Timer::Initialize()
{
    pNum_->Initialize();
}

//更新
void Timer::Update()
{
    // 起動状態か判定
    if (!active_) return;
    // フレーム更新
    if (frame_ > 0) --frame_;
}

//描画
void Timer::Draw()
{
    // テキストのサイズ
    pNum_->SetScale(defaultScale);
    pNum_->Draw(position.x, position.y, "Timer:");

    // 数字の躍動感を出す。
    // フレームを割った余りが10以下だったら
    if ((int)frame_ % FPS < movingFlame)
        pNum_->SetScale(((int)frame_ % FPS) * changeRate + defaultScale);
    else 
        pNum_->SetScale(defaultScale);

    // 秒数
    pNum_->Draw(position.x + offsetX, position.y, frame_ / FPS);
}

//開放
void Timer::Release()
{
    pNum_->Release();
    SAFE_DELETE(pNum_)
}