#pragma once

// キャラクターのステータスを管理するクラス
class CharacterBase
{
private:
    // キャラクターのステータス
    int maxHp_;         // 体力
    int attackPower_;   // 攻撃力

    // 移動関連のパラメータ
    float jumpVelocity_; // ジャンプの初速度
    float walkSpeed_;    // 歩行速度
    float runSpeed_;     // 走行速度

public:
    CharacterBase();
    ~CharacterBase();

    ///////////////////////////セッター///////////////////////////
    
    // キャラクターのステータスをセット
    void SetCharacterStatus(int maxHp, int attackPower);

    // 移動関連のパラメータをセット
    void SetMovementParameters(float jumpVelocity, float walkSpeed, float runSpeed);

    ///////////////////////////ゲッター///////////////////////////
    
    // 攻撃力取得
    int GetAttackPower() const { return attackPower_; }

    // 体力取得
    int GetMaxHp() const { return maxHp_; }

    // 跳躍力取得
    float GetJumpVelocity() const { return jumpVelocity_; }

    // 歩行速度取得
    float GetWalkSpeed() const { return walkSpeed_; }

    // 走行速度取得
    float GetRunSpeed() const { return runSpeed_; }
};