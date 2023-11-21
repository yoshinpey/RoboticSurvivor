#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"
#include "InputManager.h"

class Player : public GameObject
{
    int hModel_;                // モデル番号   
    int maxHp_, nowHp_;         // HP 

    const float JUMP_HEIGHT = 1.5f;     // ジャンプの高さ
    const float WALK_SPEED = 0.05f;     // 歩く速さ
    const float RUN_SPEED = 0.1f;      // 走る速さ

    float walkSpeed_;           // 歩行速度
    float runSpeed_;            // 走行速度
    XMFLOAT3 velocity_;         // 移動加速
    XMFLOAT3 movement_;         // 移動量
    float acceleration_;        // 加速度
    float friction_;            // 摩擦力(減速度)

    int gravity_;               // 重力
    float jumpVelocity_;        // ジャンプの初速度
    float jumpDelta_;           // 適当なごく小さい値
    bool canJump_;              // ジャンプ可能な状態かどうか

    Text* pNum;                 // テキスト

    // フラグ
    bool isMoving_;             // 移動しているかどうか

public:
    Player(GameObject* parent);     // コンストラクタ
    ~Player();                      // デストラクタ

    void Initialize() override;     // 初期化
    void Update() override;         // 更新
    void Draw() override;           // 描画
    void Release() override;        // 開放

    // アクション
    void Move();                    // プレイヤーの移動
    void Jump();                    // ジャンプ
    void PlayerHitPoint();          // 体力

    // プレイヤー座標のゲッター
    XMFLOAT3 GetPlaPos() const { return transform_.position_; }

    // ジャンプ中の物理演算
    void ApplyJumpPhysics();

    // ジャンプ可能な状態かどうか
    bool CanJump() const;

    // 地面に着地したときの処理
    void LandOnGround();

    // HP 増加
    void IncreaseHp();

    // HP 減少
    void DecreaseHp();

    // 最大速度の決定
    float DetermineMaxMoveSpeed() const;

    // 速度を目標速度に近づける
    void AccelerateToTargetSpeed(float currentSpeed, float maxMoveSpeed);

    // 最大速度を超えていたら正規化・最大値の値にする
    void ApplyMaxSpeed(float currentSpeed, float maxMoveSpeed);

    // 移動に反映
    void ApplyMovement(const XMFLOAT3& fMove);

    // 移動ボタンを離したときの減速を適応
    void ApplyDeceleration();
};
