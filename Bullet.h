#pragma once
#include "Engine/GameObject.h"

//銃弾を管理するクラス
class Bullet : public GameObject
{
    int hModel_;            //モデル番号    
    int BulletKill_;        //弾を時間で消去
    XMFLOAT3 move_;         //弾の動き

public:
    Bullet(GameObject* parent);     //コンストラクタ
    ~Bullet();                      //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    // 何かに当たった時
    void OnCollision(GameObject* pTarget);

    // 弾の動き設定用
    void SetMove(XMFLOAT3 move) { move_ = move; }
};