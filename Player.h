#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

#include "InputManager.h"

//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;                // モデル番号   
    int maxHp_, nowHp_;         // HP 

    const float JUMP_HEIGHT = 1.5f;     //ジャンプの高さ
    const float WALK_SPEED = 0.2f;      //歩く速さ
    const float RUN_SPEED = 0.3f;       //走る速さ

    float walkSpeed_;           // 歩行速度
    float runSpeed_;            // 走行速度
    XMFLOAT3 velocity_;         // 移動加速

    int gravity_;               // 重力
    float jumpVelocity_;        // 加速度
    float jumpDelta_;           // 適当なごく小さい値
    bool canJump_;              // ジャンプ可能な状態かどうか

    Text* pNum;                 //テキスト

    bool isMoving_;             // 移動しているかどうか

public:
    Player(GameObject* parent);     //コンストラクタ
    ~Player();                      //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
    
    //アクション
    void Move();                    //プレイヤーの移動
    void Jump();                    //ジャンプ
    void PlayerHitPoint();          //体力

    //プレイヤー座標のゲッター
    XMFLOAT3 GetPlaPos() { return transform_.position_; }

};