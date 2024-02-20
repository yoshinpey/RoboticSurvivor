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
    XMFLOAT3 move_;

public:
    BulletBase(GameObject* parent, BulletType bulletType, std::string name)
        :GameObject(parent, name), bulletType_(bulletType), move_(0,0,0)
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

protected:
    BulletParameter parameter_;
    
public:

    // �o���b�g�̎�ނ��擾
    BulletType GetBulletType() const { return bulletType_; }

    void SetAddSpeed(float speed) { parameter_.speed_ += speed; }

    // �o���b�g�̈ړ���ݒ�
    void SetMove(const XMFLOAT3& move) { move_ = move; }

    // �o���b�g�̈ړ����擾
    const XMFLOAT3& GetMove() const { return move_; }
};