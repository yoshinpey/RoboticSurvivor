#include "Enemy_Fly.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 0.0f, 0.0f };      // �����蔻��̈ʒu
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // ���f���̉�]
}

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pPlayer_(nullptr)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Fly", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Fly", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Fly", "attackCooldown", 0, "Settings/EnemySettings.ini");
    status_.maxHp_                      = GetPrivateProfileFloat("Enemy_Fly", "maxHp", 0, "Settings/EnemySettings.ini");
    status_.collisionScale_             = GetPrivateProfileFloat("Enemy_Fly", "collisionScale", 0, "Settings/EnemySettings.ini");

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
    SphereCollider* pCollision = new SphereCollider(collisionPosition, status_.collisionScale_);
    AddCollider(pCollision);

    transform_.rotate_.y = modelRotate.y;

    currentHp_ = status_.maxHp_;    // ���݂�HP���ő�l�ŏ�����
}

void Enemy_Fly::Update()
{
    // HP���Ȃ���Ύ��S
    if (IsDead()) KillMe();

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
        // EnemyBase�ɃL���X�g
        BulletBase* pBullet = dynamic_cast<BulletBase*>(pTarget);
        // �_���[�W��^����
        DecreaseHp(pBullet->GetBulletParameter().damage_);

        // �ђʂ��Ȃ��ꍇ�͒e�ۂ�����
        if (pBullet->GetBulletParameter().isPenetration_ == 0) pBullet->KillMe();
        else;//////�ђʂ���ꍇ�A����q�b�g�����肵�Ĉ�񂾂��_���[�W�^����悤�ɂ���
    }
}

void Enemy_Fly::Attack()
{
}

void Enemy_Fly::IncreaseHp(float amount)
{
    currentHp_ += amount;
    if (currentHp_ > status_.maxHp_) {
        currentHp_ = status_.maxHp_;
    }
}

void Enemy_Fly::DecreaseHp(float amount)
{
    currentHp_ -= amount;
    if (currentHp_ < 0) {
        currentHp_ = 0;
    }
}