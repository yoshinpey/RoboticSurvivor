#pragma once
#include "Engine/GameObject.h"

// プレイヤーの元になるクラス
class PlayerCharacterBase : public GameObject
{
public:
    PlayerCharacterBase(GameObject* parent, std::string name)
        :GameObject(parent, name)
    {
    }

    virtual ~PlayerCharacterBase() 
    {
    };

    // 移動関連のパラメータ
    struct PlayerParameter
    {
        float jumpVelocity_ = 0.2f;    // ジャンプ力
        float walkSpeed_ = 0.1f;    // 歩行速度
        float runSpeed_ = 0.2f;     // 走行速度
    };

    // ステータス
    struct PlayerStatus
    {
        float maxHp_ = 100;         // 体力
    };
};