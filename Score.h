#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Scoreを管理するクラス
class Score : public GameObject
{
    Text* pText;    //テキスト
    int score_;     //スコア
    float drawX_;    //描画位置(左右)
    float drawY_;    //描画高さ

public:
    Score(GameObject* parent);      //コンストラクタ
    ~Score();                       //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    // スコアを加算する
    void ScoreAdd(int score);            // スコアを加算する
    int GetScore();                // スコアを取得する
};