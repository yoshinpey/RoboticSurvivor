#pragma once
#include "BulletBase.h"
#include <vector>

class BulletManager
{
    std::vector<BulletBase*> bullets;  // �o���b�g�̃��X�g
    GameObject* pParent_;

public:
    BulletManager(GameObject* parent);
    ~BulletManager();

    // �o���b�g�̐������s��
    void BulletMakeing(XMFLOAT3 spawnPosition, BulletType bulletType);

    // �w�肵��bulletType�Ɉ�v����o���b�g�����S�폜����
    void RemoveBullet(BulletType bulletType);

    // ���ׂẴo���b�g�̍폜���s��
    void RemoveAllBullets();
};
