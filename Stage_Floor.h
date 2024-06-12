#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//地面モデルクラス
class Stage_Floor : public StageBase
{
    int hModel_;    //モデル番号

public:
    Stage_Floor(GameObject* parent);
    ~Stage_Floor();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // モデル番号取得用
    int GetModelHandle() const { return hModel_; }
};