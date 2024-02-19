#pragma once
#include "Engine/GameObject.h"
#include "BulletBase.h"
#include <vector>

class BulletManager
{
    std::vector<BulletBase*> Bullets;
    GameObject* pParent_;

public:
    BulletManager(GameObject* parent);
    ~BulletManager();

    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
};
