#include "Enemy_Explosion.h"
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
