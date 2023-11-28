#pragma once

// キャラクターのステータスを管理するクラス
class CharacterBase
{
protected:
    int maxHp_;          // 体力
    float jumpVelocity_; // ジャンプの初速度
    float walkSpeed_;    // 歩行速度
    float runSpeed_;     // 走行速度

    int attackPower_; // 攻撃力

public:
    CharacterBase();
    virtual ~CharacterBase();

    // すべてのキャラクターが持つパラメータ
    virtual void SetStatus(int maxHp, float jumpVelocity, float walkSpeed, float runSpeed);

    // 攻撃力
    void SetAttackPower(int attackPower);

    // 体力取得
    int GetMaxHp() const { return maxHp_; }

    // 跳躍力取得
    float GetJumpVelocity() const { return jumpVelocity_; }

    // 歩行速度取得
    float GetWalkSpeed() const { return walkSpeed_; }

    // 走行速度取得
    float GetRunSpeed() const { return runSpeed_; }

    // 攻撃力取得
    int GetAttackPower() const { return attackPower_; }
};