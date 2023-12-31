#pragma once
#include "Engine/GameObject.h"
//Playerの子供
//銃を管理するクラス
class Gun : public GameObject
{
    int hModel_;    //モデル番号
    float Bullet_speed;

public:
    Gun(GameObject* parent);        //コンストラクタ
    ~Gun();                         //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};