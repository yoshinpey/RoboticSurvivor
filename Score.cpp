#include "Score.h"

namespace
{
    XMINT2 position = { 50,700 };
}

//コンストラクタ
Score::Score(GameObject* parent) : GameObject(parent, "Score"), pText(nullptr), score_(0)
{
    pText = new Text;
}

//デストラクタ
Score::~Score()
{
}

//初期化
void Score::Initialize()
{
    pText->Initialize();
}

//更新
void Score::Update()
{
}

//描画
void Score::Draw()
{
    //pText->Draw(position.x, position.y, score_);
}

//開放
void Score::Release()
{
    pText->Release();
    SAFE_DELETE(pText)
}
