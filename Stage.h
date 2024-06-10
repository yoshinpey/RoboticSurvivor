#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//地面モデルクラス
class Stage : public StageBase
{
    int hModel_;    //モデル番号

public:
    Stage(GameObject* parent);
    ~Stage();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // モデル番号取得用
    int GetModelHandle() const { return hModel_; }
};