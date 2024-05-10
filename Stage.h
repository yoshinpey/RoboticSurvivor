#pragma once
#include "Engine/GameObject.h"

//地面モデルを管理するクラス
class Stage : public GameObject
{
    int hModel_;    //モデル番号

public:
    Stage(GameObject* parent);     //コンストラクタ
    ~Stage();                      //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    // モデル番号取得用
    int GetModelHandle() const { return hModel_; }
};