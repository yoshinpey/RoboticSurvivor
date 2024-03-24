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
    // �o���b�g�̋��ʃp�����[�^
    struct BulletParameter
    {
        float damage_;          // �_���[�W
        float shotCoolTime_;    // �N�[���^�C��
        float speed_;           // �X�s�[�h
        float killTimer_;       // ��������
        float collisionScale_;  // �����蔻��̃T�C�Y
        int isPenetration_;     // �ђ�   ����:1 �Ȃ�:0
    };
protected:
    BulletParameter parameter_; // �p�����[�^
    XMFLOAT3 move_;             // �ړ��̑��x�ƕ���
    SphereCollider* pCollision_; // �p�����[�^

public:
    BulletBase(GameObject* parent, BulletType bulletType, std::string name)
        :GameObject(parent, name), bulletType_(bulletType), move_(0,0,0), parameter_{ 0, 0, 0, 0, 0, false }, pCollision_(nullptr)
    {
    };
    virtual ~BulletBase() = default;

    // �e�e�̎�ނ��擾
    BulletType GetBulletType() const { return bulletType_; }

    // �e�e�̃p�����[�^���擾
    BulletParameter GetBulletParameter() const { return parameter_; }

    // �e�e�̈ړ���ݒ�
    void SetMove(const XMFLOAT3& move) { move_ = move; }
};