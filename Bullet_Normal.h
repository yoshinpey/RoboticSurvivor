#pragma once
#include "BulletBase.h"

class BulletBase;

// �e�e���Ǘ�����N���X
class Bullet_Normal : public BulletBase
{
    int hModel_;            // ���f���ԍ�    
    XMFLOAT3 move_;         // �e�̓���

public:
    Bullet_Normal(GameObject* parent);
    ~Bullet_Normal();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    
    BulletParameter parameter_;
 
    // �����ɓ���������
    void OnCollision(GameObject* pTarget);

    // �e�̓����ݒ�p
    void SetMove(XMFLOAT3 move) { move_ = move; }
};