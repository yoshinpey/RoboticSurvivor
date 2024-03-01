#pragma once

#include "InputManager.h"
#include "PlayerBase.h"

class Aim;
class StateManager;
class Text;

class Player : public PlayerBase
{
private:
    float nowHp_;               // HP 

    XMFLOAT3 velocity_;         // 移動加速
    XMFLOAT3 movement_;         // 移動量
    float acceleration_;        // 加速度
    float friction_;            // 摩擦力(減速度)

    float jumpFriction_;        // 滞空中の減速度
    int gravity_;               // 重力
    float jumpDelta_;           // 適当なごく小さい値
    bool jumping_;              // ジャンプ可能な状態かどうか

    //int hGroundModel_;          // モデルハンドル
    //bool useRayCast_;           // レイキャストを使うかどうか

    // インスタンス
    StateManager* pStateManager_;       // 状態を切り替える用
    Text* pText_;                        // テキスト表示用
    Aim* pAim_;                         // エイム呼び出し用

    PlayerParameter parameter_;     // パラメータ
    PlayerStatus status_;           // ステータス

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

    // 移動計算を行う関数
    XMFLOAT3 CalculateMoveInput();

    // 重力を適用する
    void ApplyGravity();

    //bool RayCastStage(XMFLOAT3 position);

    // 地面についているかどうかを判定する
    bool OnGround() const { return transform_.position_.y <= 0; }
};
