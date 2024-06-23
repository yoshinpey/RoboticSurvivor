#pragma once
#include "UIBase.h"

//HPを管理するクラス
class Gauge : public UIBase
{
    // テキスト画像の内容
    enum
    {
        FRAME = 0,
        GAUGE
    };
    std::vector<int> hPict_;    // 画像番号

    float maxHp_;               // 最大HP
    float nowHp_;               // 現在のHP

public:
    Gauge(GameObject* parent);      //コンストラクタ
    ~Gauge();                       //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    //HPセッター
    void SetHp(float maxHp, float nowHp)
    {
        maxHp_ = maxHp;
        nowHp_ = nowHp;
    }
};