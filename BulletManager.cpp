#include "BulletManager.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"

BulletManager::BulletManager(GameObject* parent) : pParent_(parent)
{
}

BulletManager::~BulletManager()
{
	// �o���b�g�̉��(�Q�[���I�u�W�F�N�g�ł���Ă邩��f���[�g�͕s�v)
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
    // ������
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
    // �w�肵��bulletType�Ɉ�v����o���b�g�����S�폜����
    for (auto it = bullets.begin(); it != bullets.end(); )
    {
        if ((*it)->GetBulletType() == bulletType)
        {
            (*it)->KillMe();        // �o���b�g�I�u�W�F�N�g���폜����
            it = bullets.erase(it); // �o���b�g�����X�g����폜���A���̗v�f���w���C�e���[�^���擾����
        }
        else
        {
            ++it;
        }
    }
}

void BulletManager::RemoveAllBullets()
{
    // �S�Ẵo���b�g�I�u�W�F�N�g���폜����
    for (auto bullet : bullets)
    {
        bullet->KillMe();
    }
    // �o���b�g���X�g���N���A����
    bullets.clear();
}
