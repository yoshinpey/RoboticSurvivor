#pragma once
#include "Engine/GameObject.h"

//浮遊敵を管理するクラス
class Enemy_Fly : public GameObject
{
    int hModel_;    //モデル番号

public:
    Enemy_Fly(GameObject* parent);  //コンストラクタ
    ~Enemy_Fly();                   //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};