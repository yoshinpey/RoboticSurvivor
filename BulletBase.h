#pragma once
#include "Engine/GameObject.h"

// �e�ۂ̖��O��ID���Ǘ�����enum
enum class BulletType
{
    NORMAL,
    EXPLOSION
};

// �e�e�̊��N���X
class BulletBase : public GameObject
{
private:
    BulletType bulletType_;

public:
    BulletBase(GameObject* parent, BulletType bulletType, std::string name)
        :GameObject(parent, name), bulletType_(bulletType)
    {
    };

    virtual ~BulletBase() = default;

    // �o���b�g�̋��ʃp�����[�^
    struct BulletParameter
    {
        float killTimer_;       // ��������
        float speed_;           // �X�s�[�h
        float damage_;          // �_���[�W
        float shotCoolTime_;    // �N�[���^�C��
        float collisionSize_;   // �����蔻��̃T�C�Y
        bool penetrationPower_; // �ђ�   ����:1 �Ȃ�:0
    };

    // �o���b�g�̎�ނ��擾
    BulletType GetBulletType() const { return bulletType_; }

    // �U��
    virtual void Attack() = 0;
};