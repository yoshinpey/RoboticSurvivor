#include "EnemyBase.h"
#include "Player.h"

namespace
{
    float rotateSpeed = 0.03f;      // �̂̉�]�X�s�[�h
    float damageTime = 1.0f;        // �_���[�W���󂯂����̃V�F�[�_�[�̓K������
    const float deltaTime = 0.05f;  // �_���[�W�̃V�F�[�_�[�̕ω���
}

// �R���X�g���N�^�̎���
EnemyBase::EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
    : Character(parent, name), enemyType_(enemyType), damageTime_(0.0f)
{
}

// �v���C���[�Ƃ̋������Z�o����
float EnemyBase::CheckPlayerDistance()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    if (!pPlayer)return 0.0f;
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    XMFLOAT3 enePos = this->GetPosition();
    return CalculateDistance(plaPos, enePos);
}

// �v���C���[�ւ̕������Z�o����
XMFLOAT3 EnemyBase::CheckPlayerDirection()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    if (!pPlayer)return { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    XMFLOAT3 enePos = this->GetPosition();
    return CalculateDirection(plaPos, enePos);
}

// �ړ����x�ɉ������ړ��ʂŃv���C���[�ɐڋ߂���
void EnemyBase::ApproachPlayer(const XMFLOAT3& directionToPlayer)
{
    // �ړ��x�N�^�[���G�l�~�[�̃|�W�V�����ɉ��Z����
    XMFLOAT3 moveVector = { directionToPlayer.x * commonParameter_.walkSpeed_, 0, directionToPlayer.z * commonParameter_.walkSpeed_ };
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

// �e�e�������������̏���
void EnemyBase::BulletHit()
{
    //�_���[�W�V�F�[�_�[�̓K�����Ԃ��Z�b�g����
    damageTime_ = damageTime;
}

// �G���m�̓����蔻�菈��
void EnemyBase::CollisionDetectionWithEnemy(EnemyBase* pEnemy)
{
//    // �Ԃ������Ώۂ̔��a�T�C�Y�𒲂ׂ�
//    float selfScale = enemyStatus_.collisionScale_;                  // ���g�̔��a
//    float enemyScale = pEnemy->GetEnemyStatus().collisionScale_;     // �Ώۂ̔��a
//
//    // �Ԃ������Ώۂ̈ʒu�����߂�
//    XMFLOAT3 selfPos = transform_.position_;        // ���g�̈ʒu
//    XMFLOAT3 targetPos = pEnemy->GetPosition();     // �Ώۂ̈ʒu
//
//    // �Ԃ������Ώۂ̕����𒲂ׂ�
//    XMFLOAT3 targetDir = CalculateDirection(targetPos, selfPos);
//
//    // �Ԃ������ΏۂƂ̋����𒲂ׂ�
//    float pushDist = CalculateDistance(targetPos, selfPos);
//
//    // �d�Ȃ�� �� 2�̂̔��a�̍��Z�l - ����
//    float overlap = (selfScale + enemyScale) - pushDist;
//
//    // �d�Ȃ�ʂ���������v�Z
//    if (overlap > 0)
//    {
//        // �d�Ȃ�ʂ𔼕��ɂ��āA�o�����ϓ��ɉ����o��
//        overlap *= 0.5f;
//
//        // �����o������
//        XMVECTOR pushBackVec = XMLoadFloat3(&targetDir) * overlap;
//
//        // �Ώۂ������o��
//        XMVECTOR newTargetPos = XMLoadFloat3(&targetPos) + pushBackVec;
//        XMStoreFloat3(&targetPos, newTargetPos);
//        pEnemy->SetPosition(targetPos);
//
//        // ���g�������o��
//        XMVECTOR newSelfPos = XMLoadFloat3(&selfPos) - pushBackVec;
//        XMStoreFloat3(&selfPos, newSelfPos);
//        transform_.position_ = selfPos;
//    }

    // ���g�ƑΏۂ̔��a���擾
    float selfScale = enemyStatus_.collisionScale_;
    float enemyScale = pEnemy->GetEnemyStatus().collisionScale_;

    // ���g�ƑΏۂ̈ʒu���擾
    XMVECTOR selfPos = XMLoadFloat3(&transform_.position_);
    XMFLOAT3 fPos = pEnemy->GetPosition();
    XMVECTOR targetPos = XMLoadFloat3(&fPos);

    // ���g�ƑΏۂ̋����x�N�g�����v�Z
    XMVECTOR dir = targetPos - selfPos;

    // �����̕������v�Z
    float distSq = XMVectorGetX(XMVector3LengthSq(dir));
    float radiusSum = selfScale + enemyScale;

    // ���a�̍��v�̕����Ƌ����̕������r
    if (distSq < radiusSum * radiusSum)
    {
        // �d�Ȃ�ʂ��v�Z
        float dist = sqrt(distSq);
        float overlap = (radiusSum - dist) * 0.5f;

        // ������0�̏ꍇ������邽�߂Ƀ`�F�b�N
        if (dist > 0)
        {
            // �����o���x�N�g�����v�Z���ēK�p
            XMVECTOR pushVec = dir / dist * overlap;
            selfPos -= pushVec;
            targetPos += pushVec;
        }
        else
        {
            // ������0�̏ꍇ�A�C�ӂ̕����ɉ����o��
            XMVECTOR pushVec = XMVectorSet(overlap, 0.0f, 0.0f, 0.0f);
            selfPos -= pushVec;
            targetPos += pushVec;
        }

        // ���ʂ𔽉f
        XMStoreFloat3(&transform_.position_, selfPos);
        XMFLOAT3 newTargetPos;
        XMStoreFloat3(&newTargetPos, targetPos);
        pEnemy->SetPosition(newTargetPos);
    }
}

// �_���[�W�V�F�[�_�[�̑O�����j
void EnemyBase::PreDrawDamageShader()
{
    if (damageTime_ > 0) {
        damageTime_ -= deltaTime;
    }
    Direct3D::damageTime = damageTime_;
}

// �_���[�W�V�F�[�_�[�̌㏈���j
void EnemyBase::PostDrawDamageShader()
{
    Direct3D::damageTime = 0.0f;
}