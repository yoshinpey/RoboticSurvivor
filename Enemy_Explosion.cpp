#include "Enemy_Explosion.h"
#include "Player.h"
#include "Engine/SphereCollider.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 1.0f, 0.0f };      // �����蔻��̈ʒu
    float collisionScale = 2.0f;                            // �����蔻��̑傫��
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1), pPlayer_(nullptr)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Explosion", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Explosion", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Explosion", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Explosion", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Explosion", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Explosion", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Explosion::~Enemy_Explosion()
{
}

void Enemy_Explosion::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Enemy/Enemy_Explosion.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionPosition, collisionScale);
    AddCollider(pCollision);

    // �v���C���[�I�u�W�F�N�g�擾
    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

void Enemy_Explosion::Update()
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

void Enemy_Explosion::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Explosion::Release()
{
}

void Enemy_Explosion::OnCollision(GameObject* pTarget)
{
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        KillMe();
    }
}

void Enemy_Explosion::Attack()
{
}

// �v���C���[�ւ̕������Z�o����
XMFLOAT3 Enemy_Explosion::CheckPlayerDirection()
{
    return CalculateDirection(this->GetPosition(), pPlayer_->GetPosition());
}

float Enemy_Explosion::CalculateDotProduct(const XMFLOAT3& directionToPlayer)
{
    // �G�l�~�[�������Ă������
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR enemyForward = XMVectorSet(sinf(rotY), 0, cosf(rotY), 0);

    // �v���C���[�ւ̕����x�N�g���Ƃ̓��ς��v�Z���Ď��E�p�x���擾
    float dotProduct;
    XMStoreFloat(&dotProduct, XMVector3Dot(enemyForward, XMLoadFloat3(&directionToPlayer)));
    return acosf(dotProduct);
}

void Enemy_Explosion::ApproachPlayer(const XMFLOAT3& directionToPlayer)
{
    // �ړ��x�N�^�[���G�l�~�[�̃|�W�V�����ɉ��Z����
    XMFLOAT3 moveVector = { directionToPlayer.x * status_.walkSpeed_, 0, directionToPlayer.z * status_.walkSpeed_ };
    transform_.position_ = CalculateFloat3Add(transform_.position_, moveVector);
}

void Enemy_Explosion::RotateTowardsPlayer(const XMFLOAT3& directionToPlayer)
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