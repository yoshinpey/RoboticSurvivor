#pragma once
#include "BulletBase.h"

class BulletBase;

// �e�e���Ǘ�����N���X
class Bullet_Explosion : public BulletBase
{
    int hModel_;            // ���f���ԍ�    
public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // �����ɓ���������
    void OnCollision(GameObject* pTarget);

    // �o���b�g�̃p�����[�^���擾
    const BulletParameter& GetParameter() const { return parameter_; }
};