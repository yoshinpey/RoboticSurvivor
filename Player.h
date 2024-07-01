#pragma once
#include "InputManager.h"
#include "Character.h"

class Aim;
class StateManager;
class Text;
class Gauge;

class Player : public Character
{
private:

    // プレイヤー固有のパラメータ
    struct PlayerParameter
    {
        XMFLOAT3 velocity_{ 0.0f, 0.0f, 0.0f };      // 移動速度
        XMFLOAT3 movement_{ 0.0f, 0.0f, 0.0f };      // 移動量
        float acceleration_{ 0.03f };                // 加速度
        float friction_{ 0.85f };                    // 摩擦力(減速度)
        float jumpFriction_{ 1.15f };                // 滞空中の減速度
        int gravity_{ -1 };                          // 重力
        float jumpDelta_{ 0.01f };                   // ジャンプの高さ
        bool jumping_{ false };                      // ジャンプ中フラグ

        PlayerParameter() = default;
    };

    // インスタンス
    PlayerParameter playerParams_;      // プレイヤー固有のパラメータ
    StateManager* pStateManager_;       // 状態を切り替える用
    Aim* pAim_;                         // エイム呼び出し用
    Gauge* pGauge_;                     // HPゲージ

    bool isEnemyHit_;                   // エネミーに当たったとき真(無敵時間設定用)
    XMFLOAT3 knockDirection_;           // ノックバック方向

public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // 歩く
    void Walk();

    // 走る
    void Run();

    // 移動適応
    void ApplyMovement(const XMFLOAT3& moveVector, float maxSpeed);

    // 減速適応
    void ApplyDeceleration();

    // ジャンプ
    void Jump();

    // 移動計算
    XMFLOAT3 CalculateMoveInput();

    // 重力を適用
    void ApplyGravity();

    // 何かに当たった
    void OnCollision(GameObject* pTarget) override;

    // ノックバック適応関数
    void ApplyKnockback();

    // 無敵中かどうか
    bool IsInvincible() const { return isEnemyHit_; }
};
