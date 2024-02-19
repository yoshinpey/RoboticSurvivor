#pragma once
#include "BulletBase.h"
#include <vector>

class BulletManager
{
    std::vector<BulletBase*> bullets;  // バレットのリスト
    GameObject* pParent_;

public:
    BulletManager(GameObject* parent);
    ~BulletManager();

    // バレットの生成を行う
    void BulletMakeing(XMFLOAT3 spawnPosition, BulletType bulletType);

    // 指定したbulletTypeに一致するバレットだけ全削除する
    void RemoveBullet(BulletType bulletType);

    // すべてのバレットの削除を行う
    void RemoveAllBullets();
};
