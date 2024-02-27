#include "Enemy_Ground.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr), lastAngle_(0)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Ground", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Ground", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Ground", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Ground", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Ground::~Enemy_Ground()
{
}

void Enemy_Ground::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Enemy_02.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    //Model::SetAnimFrame(hModel_, 0, 120, 0.75);

    // �����蔻��t�^
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 1.5f);
    AddCollider(pCollision_);
}

void Enemy_Ground::Update()
{
    // �v���C���[�ւ̕����x�N�g��(���K����)
    XMFLOAT3 directionToPlayer = CheckPlayerDirection();

    // �v���C���[�Ƃ̓��ς��v�Z���Ď��E�p�x���擾
    float dotProduct = CalculateDotProduct(directionToPlayer);
    const float fovAngle = XMConvertToRadians(1.0f);

    // �v���C���[�����E���ɂ���ꍇ
    if (dotProduct >= fovAngle)
    {
        // ���E���ɂ��邱�Ƃ��������߂ɃX�P�[����ύX
        transform_.scale_.y = 1.0f;

        // �����ꂽ�����܂Ńv���C���[�ɐڋ�
        if (algorithm_.approachDistance_ <= CheckPlayerDistance())
        {
            ApproachPlayer(directionToPlayer);
            // �f�o�b�O�p�A�v���C���[�܂ł̋�����\��
            OutputDebugString(std::to_string(CheckPlayerDistance()).c_str());
            OutputDebugString("\n");
        }

        // �v���C���[�̕����������悤�Ɏ��E����]
        RotateTowardsPlayer(directionToPlayer);
    }
    else
    {
        // ���E���ɂ��Ȃ��Ƃ��Ԃ�
        transform_.scale_.y = 0.5f;

    }
}

float Enemy_Ground::CalculateDotProduct(const XMFLOAT3& directionToPlayer)
{
    // �G�l�~�[�������Ă������
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR enemyForward = XMVectorSet(sinf(rotY), 0, cosf(rotY), 0);

    // �v���C���[�ւ̕����x�N�g���Ƃ̓��ς��v�Z���Ď��E�p�x���擾
    float dotProduct;
    XMStoreFloat(&dotProduct, XMVector3Dot(enemyForward, XMLoadFloat3(&directionToPlayer)));
    return acosf(dotProduct);
}

void Enemy_Ground::ApproachPlayer(const XMFLOAT3& directionToPlayer)
{

    XMFLOAT3 moveVector = { directionToPlayer.x * status_.walkSpeed_, 0, directionToPlayer.z * status_.walkSpeed_ };
    transform_.position_ = CalculateFloat3Add(transform_.position_, moveVector);
}

void Enemy_Ground::RotateTowardsPlayer(const XMFLOAT3& directionToPlayer)
{
    // �v���C���[�ւ̋t�x�N�g��(��������������)
    XMVECTOR playerBackward = XMVector3Normalize(XMVectorSet(-directionToPlayer.x, 0, -directionToPlayer.z, 0));

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

void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{
    /*
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Ground::Attack()
{
}

