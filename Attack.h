#pragma once
#include "Engine/GameObject.h"

//近接攻撃を管理するクラス
class Attack : public GameObject
{
    int hModel_;    //モデル番号

public:
    Attack(GameObject* parent);//コンストラクタ
    ~Attack();//デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};