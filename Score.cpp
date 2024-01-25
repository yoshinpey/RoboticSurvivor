#include "Score.h"

//コンストラクタ
Score::Score(GameObject* parent)
    :GameObject(parent, "Score"), pText(nullptr), 
    drawX_(50), drawY_(700)
{
}

//デストラクタ
Score::~Score()
{
}

//初期化
void Score::Initialize()
{
    pText = new Text;
    pText->Initialize();
}

//更新
void Score::Update()
{
}

//描画
void Score::Draw()
{
    pText->Draw((int)drawX_, (int)drawY_, score_);
}

//開放
void Score::Release()
{
    delete pText;
    pText = nullptr;
}

//スコアを加算する
void Score::ScoreAdd(int score)
{
    score_ += score;
}

//スコアを取得する
int Score::GetScore()
{
    return score_;
}