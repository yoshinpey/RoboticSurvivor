#pragma once
#include "Character.h"

// マルチに対応したら意味が出るかも知れない程度の無意味クラス
class PlayerBase : public Character
{
    // 移動関連の構造体
    struct MovementParameters 
    {
        XMFLOAT3 velocity{ 0.0f, 0.0f, 0.0f };      // 移動加速
        XMFLOAT3 movement{ 0.0f, 0.0f, 0.0f };      // 移動量
        float acceleration{ 0.03f };                // 加速度
        float friction{ 0.85f };                    // 摩擦力(減速度)
        float jumpFriction{ 1.15f };                // 滞空中の減速度
        int gravity{ -1 };                          // 重力
        float jumpDelta{ 0.01f };                   // 適当なごく小さい値
        bool jumping{ false };                      // ジャンプ可能な状態かどうか

        // デフォルトコンストラクタ
        MovementParameters() = default;
    };

protected:
    MovementParameters movementParams_;  // 移動関連のパラメータ

public:
    PlayerBase(GameObject* parent, std::string name)
        : Character(parent, name)
    {
    }

    virtual ~PlayerBase() = default;
};
