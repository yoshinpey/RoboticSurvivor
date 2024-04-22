#include "Enemy_Ground.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 1.0f, 0.0f };      // �����蔻��̈ʒu
    float collisionScale = 1.5f;                            // �����蔻��̑傫��
}

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), lastAngle_(0), pPlayer_(nullptr)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    status_.maxHp_                      = GetPrivateProfileFloat("Enemy_Ground", "maxHp", 0, "Settings/EnemySettings.ini");
    currentHp_ = status_.maxHp_;    // ���݂�HP���ő�l�ŏ�����

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
    hModel_ = Model::Load("Enemy/Enemy_Ground.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    //Model::SetAnimFrame(hModel_, 0, 120, 0.75);
     
    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionPosition, collisionScale);
    AddCollider(pCollision);

    transform_.rotate_.y = 180;

    currentHp_ = status_.maxHp_;    // ���݂�HP���ő�l�ŏ�����
}

void Enemy_Ground::Update()
{
    // HP���Ȃ���Ύ��S
    if (currentHp_ <= 0)
    { 
        KillMe(); 
    }

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
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        // EnemyBase�ɃL���X�g
        BulletBase* pBullet = dynamic_cast<BulletBase*>(pTarget);
        // �_���[�W��^����
        DecreaseHp(pBullet->GetBulletParameter().damage_);

        // �ђʂ��Ȃ��ꍇ�͒e�ۂ�����
        if (pBullet->GetBulletParameter().isPenetration_ == 0) pBullet->KillMe();
        else;//////�ђʂ���ꍇ�q�b�g�����񂩔��肵�Ĉ�񂾂��_���[�W�^����悤�ɂ���
    }
}

void Enemy_Ground::Attack()
{
}

void Enemy_Ground::IncreaseHp(float amount)
{
    currentHp_ += amount;
    if (currentHp_ > status_.maxHp_) {
        currentHp_ = status_.maxHp_;
    }
}

void Enemy_Ground::DecreaseHp(float amount)
{
    currentHp_ -= amount;
    if (currentHp_ < 0) {
        currentHp_ = 0;
    }
}
