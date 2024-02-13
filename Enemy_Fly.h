#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

//浮遊敵を管理するクラス
class Enemy_Fly : public EnemyBase
{
    int hModel_;    //モデル番号
    SphereCollider* pCollision_;
    //PlayerCharacterBase characterStatus_;
    ///////////////////////////定数///////////////////////////
    //const float JUMP_HEIGHT = 1.50f;    // ジャンプの高さ
    //const float WALK_SPEED = 0.07f;     // 歩く速さ
    //const float RUN_SPEED = 0.10f;      // 走る速さ
    //const float ATK = 1.0f;             // 攻撃力
    //const float MAX_HP = 1.0f;          // 体力
    //////////////////////////////////////////////////////////

    // 各ステータス
    float walkSpeed_;
    float attackPower_;
    float attackCooldown_;
    float detectPlayerDistance_;
    float patrolRadius_;
    float approachDistance_;
    float attackDistance_;

public:
    Enemy_Fly(GameObject* parent);  // コンストラクタ
    ~Enemy_Fly();                   // デストラクタ
    void Initialize() override;     // 初期化
    void Update() override;         // 更新
    void Draw() override;           // 描画
    void Release() override;        // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget) override;

    void Attack() override;

    /*
    void loadStatsFromXML(const std::string& filename);
    void LoadWalkSpeedFromJson(const std::string& filename);
    */
};