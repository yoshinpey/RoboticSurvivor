#pragma once
#include "Engine/GameObject.h"

//浮遊敵を管理するクラス
class Enemy_Fly : public GameObject
{
    int hModel_;    //モデル番号
    const float JUMP_HEIGHT = 1.0f;     // ジャンプの高さ
    const float WALK_SPEED = 0.05f;     // 歩く速さ
    const float RUN_SPEED = 0.10f;      // 走る速さ
public:
    Enemy_Fly(GameObject* parent);  //コンストラクタ
    ~Enemy_Fly();                   //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};