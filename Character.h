#pragma once
#include "Engine/GameObject.h"

class Character : public GameObject
{
protected:
    // 移動関連のパラメータ
    struct CharacterParameter
    {
        float jumpVelocity_ = 0.2f;     // ジャンプ力
        float walkSpeed_ = 0.1f;        // 歩行速度
        float runSpeed_ = 0.2f;         // 走行速度
    };

    // ステータス
    struct CharacterStatus
    {
        float maxHp_ = 100;         // 体力
        float currentHp_ = 100;     // 現在の体力
    };

    CharacterParameter parameter_;
    CharacterStatus status_;

public:
    Character(GameObject* parent, std::string name)
        : GameObject(parent, name)
    {
    }

    virtual ~Character()
    {
    };

    // HPを増やす
    void IncreaseHp(float amount)
    {
        status_.currentHp_ += amount;
        if (status_.currentHp_ > status_.maxHp_) {
            status_.currentHp_ = status_.maxHp_;
        }
    }

    // HPを減らす
    void DecreaseHp(float amount)
    {
        status_.currentHp_ -= amount;
        if (status_.currentHp_ < 0) {
            status_.currentHp_ = 0;
        }
    }

    // 何かに当たった
    virtual void OnCollision(GameObject* pTarget) = 0;

    float GetCurrentHp() const { return status_.currentHp_; }
    float GetMaxHp() const { return status_.maxHp_; }
};
