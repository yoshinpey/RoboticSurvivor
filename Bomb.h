#pragma once
#include "Engine/GameObject.h"

//爆弾を管理するクラス
class Bomb : public GameObject
{
    int hModel_;    //モデル番号

public:
    Bomb(GameObject* parent);       //コンストラクタ
    ~Bomb();                        //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};