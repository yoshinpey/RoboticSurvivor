#pragma once
#include "Engine/GameObject.h"

//地上敵を管理するクラス
class Enemy_Ground : public GameObject
{
    int hModel_;    //モデル番号

public:
    Enemy_Ground(GameObject* parent);//コンストラクタ
    ~Enemy_Ground();                //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};