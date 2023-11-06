#pragma once
#include "Engine/GameObject.h"

//守護目標(クリスタル)を管理するクラス
class Crystal : public GameObject
{
    int hModel_;    //モデル番号

public:
    Crystal(GameObject* parent);    //コンストラクタ
    ~Crystal();                     //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};