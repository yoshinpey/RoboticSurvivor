#include "Enemy_Fly.h"
#include "Player.h"
#include "Engine/SphereCollider.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 0.0f, 0.0f };      // �����蔻��̈ʒu
    float collisionScale = 1.0f;                            // �����蔻��̑傫��
}

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pPlayer_(nullptr)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Fly", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Fly", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Fly", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Fly", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Fly", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Fly", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Fly", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Fly::~Enemy_Fly()
{
}

void Enemy_Fly::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Enemy/Enemy_Fly.fbx");
    assert(hModel_ >= 0);

    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionPosition, collisionScale);
    AddCollider(pCollision);

    transform_.rotate_.y = 180;

    // �v���C���[�I�u�W�F�N�g�擾
    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

void Enemy_Fly::Update()
{

    // �v���C���[�ւ̕����x�N�g��(���K����)
    XMFLOAT3 directionToPlayer = CheckPlayerDirection();

    // �v���C���[�Ƃ̓��ς��v�Z���Ď��E�p�x���擾
    float dotProduct = CalculateDotProduct(directionToPlayer);
    const float fovAngle = XMConvertToRadians(1.0f);

    // �v���C���[�����E���ɂ���ꍇ
    if (dotProduct >= fovAngle)
    {
        // �����ꂽ�����܂Ńv���C���[�ɐڋ�
        if (algorithm_.attackDistance_ <= CheckPlayerDistance())
        {
            ApproachPlayer(directionToPlayer);
        }

        // �v���C���[�̕����������悤�Ɏ��E����]
        RotateTowardsPlayer(directionToPlayer);
    }
    else
    {
        // ���E���ɂ��Ȃ��Ƃ��Ԃ�
        //transform_.scale_.y = 0.5f;

    }
}

void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Fly::Release()
{
}

void Enemy_Fly::OnCollision(GameObject* pTarget)
{
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        KillMe();
    }
}

void Enemy_Fly::Attack()
{
}

// �v���C���[�ւ̕������Z�o����
XMFLOAT3 Enemy_Fly::CheckPlayerDirection()
{
    return CalculateDirection(this->GetPosition(), pPlayer_->GetPosition());
}

float Enemy_Fly::CalculateDotProduct(const XMFLOAT3& directionToPlayer)
{
    // �G�l�~�[�������Ă������
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR enemyForward = XMVectorSet(sinf(rotY), 0, cosf(rotY), 0);

    // �v���C���[�ւ̕����x�N�g���Ƃ̓��ς��v�Z���Ď��E�p�x���擾
    float dotProduct;
    XMStoreFloat(&dotProduct, XMVector3Dot(enemyForward, XMLoadFloat3(&directionToPlayer)));
    return acosf(dotProduct);
}

void Enemy_Fly::ApproachPlayer(const XMFLOAT3& directionToPlayer)
{
    // �ړ��x�N�^�[���G�l�~�[�̃|�W�V�����ɉ��Z����
    XMFLOAT3 moveVector = { directionToPlayer.x * status_.walkSpeed_, 0, directionToPlayer.z * status_.walkSpeed_ };
    transform_.position_ = CalculateFloat3Add(transform_.position_, moveVector);
}

void Enemy_Fly::RotateTowardsPlayer(const XMFLOAT3& directionToPlayer)
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
    float angle = atan2(XMVectorGetY(cross), dot);
    transform_.rotate_.y += XMConvertToDegrees(angle) * 0.03f;
}

