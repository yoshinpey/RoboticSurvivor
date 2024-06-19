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
        float knockBackStrength_; // ノックバックの強さ

        CommonParameter();
    };

    // ステータス
    struct CommonStatus
    {
        float maxHp_;         // 体力
        float currentHp_;     // 現在の体力

        CommonStatus();
    };

    CommonParameter commonParameter_;
    CommonStatus commonStatus_;

    // ノックバック関連
    XMFLOAT3 knockDirection_;
    bool isKnockBackActive_;

public:
    Character(GameObject* parent, std::string name);
    virtual ~Character();

    // 更新メソッド
    virtual void Update();

    // HPを増やす
    void IncreaseHp(float amount);

    // HPを減らす
    void DecreaseHp(float amount);

    // 死亡判定
    bool IsCharacterDead();

    // ノックバック処理
    void KnockBack(const XMFLOAT3& direction, float strength);
};
