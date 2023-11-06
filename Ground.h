#pragma once
#include "Engine/GameObject.h"

//地面モデルを管理するクラス
class Ground : public GameObject
{
    int hModel_;    //モデル番号

public:
    Ground(GameObject* parent);     //コンストラクタ
    ~Ground();                      //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    //あたり判定
    void OnCollision(GameObject* pTarget) override;
};