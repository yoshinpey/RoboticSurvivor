#pragma once
#include "InputManager.h"
#include "PlayerBase.h"

class Aim;
class StateManager;
class Text;
class Gauge;

class Player : public PlayerBase
{
private:

private:
    // インスタンス
    StateManager* pStateManager_;       // 状態を切り替える用
    Text* pText_;                       // テキスト表示用
    Aim* pAim_;                         // エイム呼び出し用
    Gauge* pGauge_;                     // HPゲージ

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
    void PlayerHitPoint();          // 体力
    XMFLOAT3 CalculateMoveInput();  // 移動計算
    void ApplyGravity();            // 重力を適用
    void OnCollision(GameObject* pTarget) override; // 何かに当たった

    // 地面についているかどうかを判定
    bool Jumping() const { return transform_.position_.y >= 0; }
};
