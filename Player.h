#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;                //モデル番号   
    int maxHp_, nowHp_;         //HP 

    float jampVelocity_;        //ジャンプ速度
    float fuel_;                //燃料
    float maxFuel_;             //最大燃料
    float jumpCool_;            //クールタイム
    float gravity_;             //重力
    bool CanJump_;              //ジャンプ可能か

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
    void JetPack();                 //ジェットパック
    void BoostJump();               //組み合わせ
    void PlayerHitPoint();          //体力
    void CameraPosition();          //視点

    //プレイヤー座標のゲッター
    XMFLOAT3 GetPlaPos() { return transform_.position_; }

};