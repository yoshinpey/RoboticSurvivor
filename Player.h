#pragma once
#include "Engine/Text.h"

#include "InputManager.h"
#include "StateManager.h"
#include "CharacterBase.h"

class Aim;

class Player : public CharacterBase
{
private:
    int maxHp_, nowHp_;                 // HP 
    ///////////////////////////定数///////////////////////////
    const float JUMP_HEIGHT = 0.2f;     // ジャンプの高さ
    const float WALK_SPEED = 0.1f;      // 歩く速さ
    const float RUN_SPEED = 0.2f;       // 走る速さ

    const float ATK = 0.0f;             // 攻撃力
    const float MAX_HP = 1.0f;          // 体力
    //////////////////////////////////////////////////////////

    float walkSpeed_;           // 歩行速度
    float runSpeed_;            // 走行速度
    XMFLOAT3 velocity_;         // 移動加速
    XMFLOAT3 movement_;         // 移動量
    float acceleration_;        // 加速度
    float friction_;            // 摩擦力(減速度)
    float jumpFriction_;        // 摩擦力(減速度)

    int gravity_;               // 重力
    float jumpVelocity_;        // ジャンプの初速度
    float jumpDelta_;           // 適当なごく小さい値
    bool canJump_;              // ジャンプ可能な状態かどうか
    XMFLOAT3 jumpDirection_;    // ジャンプする直前の方向
    XMFLOAT3 jumpSpeed_;        // ジャンプする直前の速度

    // インスタンス
    StateManager* stateManager_;        // 状態を切り替える用    
    CharacterBase* pCharacterBase_;    // キャラクターが持つパラメータ
    Text* pNum;                         // テキスト
    Aim* pAim_;                         // エイム

public:
    Player(GameObject* parent);     // コンストラクタ
    ~Player();                      // デストラクタ

    void Initialize() override;     // 初期化
    void Update() override;         // 更新
    void Draw() override;           // 描画
    void Release() override;        // 開放

    // アクション
    void Walk();                    // 歩く
    void Run();                     // 走る
    void ApplyMovement(const XMFLOAT3& moveVector, float speed);
    void ApplyDeceleration();       
    void Jump();                    // ジャンプ
    void PlayerHitPoint();          // 体力

    // プレイヤー座標のゲッター
    XMFLOAT3 GetPlaPos() const { return transform_.position_; }

    // 移動計算を行う関数
    XMFLOAT3 CalculateMoveInput();

    // 正規化を行う関数
    void Normalize(XMFLOAT3& vec);

    // 地面についているかどうかを判定する
    bool OnGround() const { return transform_.position_.y <= 0; }
};
