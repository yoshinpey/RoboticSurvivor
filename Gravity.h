#pragma once
#include "Engine/GameObject.h"

//  重力を管理するクラス
class Gravity : public GameObject
{
private:
    float gravity_;                 //重力
public:
    Gravity(GameObject* parent);    //コンストラクタ
    ~Gravity();                     //デストラクタ

    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    //重力セット
    float AddGravity(float _transPosY)
    {
        return (_transPosY += gravity_);
    }
};