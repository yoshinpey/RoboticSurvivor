#pragma once
class CharacterBase
{
protected:
    int maxHp_;          // 体力
    float jumpVelocity_; // ジャンプの初速度
    float walkSpeed_;    // 歩行速度
    float runSpeed_;     // 走行速度

public:
    CharacterBase();
    virtual ~CharacterBase();

    void SetStatus(int maxHp, float jumpVelocity, float walkSpeed, float runSpeed);
};