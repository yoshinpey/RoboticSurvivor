#include "BulletManager.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"

BulletManager::BulletManager(GameObject* parent) : pParent_(parent)
{
}

BulletManager::~BulletManager()
{
	// バレットの解放(ゲームオブジェクトでやってるからデリートは不要)
	bullets.clear();
}

void BulletManager::BulletMakeing(XMFLOAT3 spawnPosition, BulletType bulletType)
{
	BulletBase* pNewBullet = nullptr;
    switch (bulletType)
    {
    case BulletType::NORMAL:
        pNewBullet = Instantiate<Bullet_Normal>(pParent_);
        static_cast<Bullet_Normal*>(pNewBullet)->SetPosition(spawnPosition);
        break;
    // 未実装
    //case BulletType::EXPLOSION:
    //    pNewBullet = Instantiate<Bullet_Explosion>(pParent_);
    //    static_cast<Bullet_Explosion*>(pNewBullet)->SetPosition(spawnPosition);
    //    break;
    }

    if (pNewBullet != nullptr)
    {
        bullets.push_back(pNewBullet);
    }
}

void BulletManager::RemoveBullet(BulletType bulletType)
{
    // 指定したbulletTypeに一致するバレットだけ全削除する
    for (auto it = bullets.begin(); it != bullets.end(); )
    {
        if ((*it)->GetBulletType() == bulletType)
        {
            (*it)->KillMe();        // バレットオブジェクトを削除する
            it = bullets.erase(it); // バレットをリストから削除し、次の要素を指すイテレータを取得する
        }
        else
        {
            ++it;
        }
    }
}

void BulletManager::RemoveAllBullets()
{
    // 全てのバレットオブジェクトを削除する
    for (auto bullet : bullets)
    {
        bullet->KillMe();
    }
    // バレットリストをクリアする
    bullets.clear();
}
