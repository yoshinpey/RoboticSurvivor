#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;                // モデル番号   
    int maxHp_, nowHp_;         // HP 

    float gravity_;             // 重力
    float jumpVelocity_;        // 加速度
    float jumpDelta_;           // 適当なごく小さい値                    
    float flightTime_;          // ジャンプ経過時間
    bool canJump_;              // ジャンプ可能な状態かどうか

    Text* pNum;                 //テキスト

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