#pragma once
#include "Engine/GameObject.h"

//銃を管理するクラス
class Gun : public GameObject
{
    int hModel_;    //モデル番号
    float bulletSpeed_;
    float AttackCool_;
    float Cool_;
public:
    Gun(GameObject* parent);        //コンストラクタ
    ~Gun();                         //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    // 銃弾の速度と射出方向を計算する
    XMFLOAT3 CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed);

    // 銃弾を生成する
    template<class T>
    void ShootBullet();
};