#pragma once
#include "Engine/GameObject.h"

class Character : public GameObject
{
protected:
    // 移動関連のパラメータ
    struct CommonParameter
    {
        float jumpVelocity_;     // ジャンプ力
        float walkSpeed_;        // 歩行速度
        float runSpeed_;         // 走行速度

        CommonParameter()
            : jumpVelocity_(0.2f), walkSpeed_(0.1f), runSpeed_(0.2f)
        {
        }
    };

    // ステータス
    struct CommonStatus
    {
        float maxHp_;         // 体力
        float currentHp_;     // 現在の体力
        CommonStatus()
            : maxHp_(100.0f), currentHp_(maxHp_)
        {
        }
    };

    CommonParameter commonParameter_;
    CommonStatus commonStatus_;

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
        commonStatus_.currentHp_ += amount;
        if (commonStatus_.currentHp_ > commonStatus_.maxHp_) {
            commonStatus_.currentHp_ = commonStatus_.maxHp_;
        }
    }

    // HPを減らす
    void DecreaseHp(float amount)
    {
        commonStatus_.currentHp_ -= amount;
        if (commonStatus_.currentHp_ < 0) {
            commonStatus_.currentHp_ = 0;
        }
    }
    float GetCurrentHp() const { return commonStatus_.currentHp_; }
    float GetMaxHp() const { return commonStatus_.maxHp_; }
};
