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

    bool isEnemyHit_;
    XMFLOAT3 knockDirection_;

public:
    Player(GameObject* parent);     // コンストラクタ
    ~Player();                      // デストラクタ

    void Initialize() override;     // 初期化
    void Update() override;         // 更新
    void Draw() override;           // 描画
    void Release() override;        // 開放

    void Walk();                    // 歩く
    void Run();                     // 走る
    void ApplyMovement(const XMFLOAT3& moveVector, float speed);    // 移動適応
    void ApplyDeceleration();       // 減速適応
    void Jump();                    // ジャンプ
    XMFLOAT3 CalculateMoveInput();  // 移動計算
    void ApplyGravity();            // 重力を適用
    void OnCollision(GameObject* pTarget) override; // 何かに当たった

    // 地面についているかどうかを判定
    bool Jumping() const { return transform_.position_.y >= 0; }
};
