#pragma once
#include "Engine/GameObject.h"

//HPを管理するクラス
class Gauge : public GameObject
{
    int hpPict_[2];    //画像番号
    int maxHp_, nowHp_;

public:
    Gauge(GameObject* parent);      //コンストラクタ
    ~Gauge();                       //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    //HPセッター
    void SetHp(int maxHp, int nowHp)
    {
        maxHp_ = maxHp;
        nowHp_ = nowHp;
    }
};