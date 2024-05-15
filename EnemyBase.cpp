#include "EnemyBase.h"
#include "Player.h"

namespace
{
    float rotateSpeed = 0.03f;
}

// �R���X�g���N�^�̎���
EnemyBase::EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
    : GameObject(parent, name), enemyType_(enemyType), currentHp_(0.0f)
{
    status_ = { 0,0,0,0 };
    algorithm_ = { 0,0,0,0 };
}

// �v���C���[�Ƃ̋������Z�o����
float EnemyBase::CheckPlayerDistance()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    XMFLOAT3 enePos = this->GetPosition();
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    return CalculateDistance(enePos, plaPos);
}

// �v���C���[�ւ̕������Z�o����
XMFLOAT3 EnemyBase::CheckPlayerDirection()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    XMFLOAT3 enePos = this->GetPosition();
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    return CalculateDirection(enePos, plaPos);
}

// ���όv�Z(����p�v�Z)
float EnemyBase::CalculateDotProduct(const XMFLOAT3& directionToPlayer)
{
    // �G�l�~�[�������Ă������
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR enemyForward = XMVector3Normalize(XMVectorSet(sinf(rotY), 0, cosf(rotY), 0));

    // �v���C���[�ւ̕����x�N�g���Ƃ̓��ς��v�Z���Ď��E�p�x���擾
    float dotProduct;
    XMStoreFloat(&dotProduct, XMVector3Dot(enemyForward, XMLoadFloat3(&directionToPlayer)));
    return acosf(dotProduct);
}

// �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
void EnemyBase::ApproachPlayer(const XMFLOAT3& directionToPlayer)
{
    // �ړ��x�N�^�[���G�l�~�[�̃|�W�V�����ɉ��Z����
    XMFLOAT3 moveVector = { directionToPlayer.x * status_.walkSpeed_, 0, directionToPlayer.z * status_.walkSpeed_ };
    transform_.position_ = CalculateFloat3Add(transform_.position_, moveVector);
}

// �G�̑̂��v���C���[�̕����։�]������
void EnemyBase::RotateTowardsPlayer(const XMFLOAT3& directionToPlayer)
{
    // �v���C���[�ւ̋t�x�N�g��(��������������)
    XMVECTOR playerBackward = XMVector3Normalize(XMVectorSet(directionToPlayer.x, 0, directionToPlayer.z, 0));

    // �G�l�~�[�������Ă������
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR enemyForward = XMVector3Normalize(XMVectorSet(sinf(rotY), 0, cosf(rotY), 0));

    // ���ςƊO�ς��v�Z
    float dot = XMVectorGetX(XMVector3Dot(enemyForward, playerBackward));
    XMVECTOR cross = XMVector3Cross(enemyForward, playerBackward);

    // �p�x���v�Z���ĉ�]
    float angle = static_cast<float>(atan2(XMVectorGetY(cross), dot));
    transform_.rotate_.y += XMConvertToDegrees(angle) * rotateSpeed;
}
