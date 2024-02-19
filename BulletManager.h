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

    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};
