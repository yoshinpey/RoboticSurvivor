#pragma once
#include "Engine/GameObject.h"

// ステージの種類
enum class StageType
{
    FLOOR,
    SKYBOX,
    MAX
};

// ステージオブジェクトのもとになるクラス
class StageBase : public GameObject
{
protected:
    StageType stageType_; // ステージの種類

public:
    StageBase(GameObject* parent, StageType stageType, std::string name)
        : GameObject(parent, name), stageType_(stageType) 
    {
    }

    virtual ~StageBase() = default;

    // ステージの種類を取得
    StageType GetStageType() const { return stageType_; }
};