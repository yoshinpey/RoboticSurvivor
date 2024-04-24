#include "Enemy_Explosion.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 1.0f, 0.0f };        // �����蔻��̈ʒu
    XMFLOAT3 modelRotate = { 0.0f, 0.0f, 0.0f };          // ���f���̉�]
    struct AnimFrame
    {
        float startFrame = 0.0f;
        float endFrame = 100.0f;
        float speed = 0.75f;
    };
    AnimFrame anim;
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1)/*, isFirstHit_(true), firstPosition_{0,0,0}*/, currentHp_(0)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Explosion", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Explosion", "attackCooldown", 0, "Settings/EnemySettings.ini");
    status_.maxHp_                      = GetPrivateProfileFloat("Enemy_Explosion", "maxHp", 0, "Settings/EnemySettings.ini");
    status_.collisionScale_             = GetPrivateProfileFloat("Enemy_Explosion", "collisionScale", 0, "Settings/EnemySettings.ini");

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
    Model::SetAnimFrame(hModel_, anim.startFrame, anim.endFrame, anim.speed);

    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionOffset, status_.collisionScale_);
    AddCollider(pCollision);

    // ���f���̉�]
    transform_.rotate_.y = modelRotate.y;

    // ���݂�HP���ő�l�ŏ�����
    currentHp_ = status_.maxHp_;    
}

void Enemy_Explosion::Update()
{
    /////////////����{���̓}�l�[�W���[�ʂ��Ȃ��Ƃ����Ȃ�
    // HP���Ȃ���Ύ��S
    //if (IsDead()) KillMe();

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
        // EnemyBase�ɃL���X�g
        BulletBase* pBullet = dynamic_cast<BulletBase*>(pTarget);

        // ���łɂ��̓G�ɑ΂��ăq�b�g�ς݂̏ꍇ�͖���
        if (hitEnemies.find(pTarget) != hitEnemies.end())return;

        // �_���[�W��^����
        DecreaseHp(pBullet->GetBulletParameter().damage_);

        // �q�b�g���L�^
        hitEnemies.insert(pTarget);

        // �ђʂ��Ȃ��ꍇ�͒e�ۂ�����
        if (pBullet->GetBulletParameter().isPenetration_ == 0)
        {
            pBullet->KillMe();
        }
    }
};

void Enemy_Explosion::Attack()
{
}

void Enemy_Explosion::IncreaseHp(float amount)
{
    currentHp_ += amount;
    if (currentHp_ > status_.maxHp_) {
        currentHp_ = status_.maxHp_;
    }
}

void Enemy_Explosion::DecreaseHp(float amount)
{
    currentHp_ -= amount;
    if (currentHp_ < 0) {
        currentHp_ = 0;
    }
}