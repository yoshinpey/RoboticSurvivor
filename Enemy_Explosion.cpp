#include "Enemy_Explosion.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 1.0f, 0.0f };        // �����蔻��̈ʒu
    XMFLOAT3 modelRotate = { 0.0f, 0.0f, 0.0f };          // ���f���̉�]
    struct AnimFrame
    {
        int startFrame = 0;
        int endFrame = 100;
        float speed = 0.75f;
    };
    AnimFrame anim;
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_                         = GetPrivateProfileFloat("Enemy_Explosion", "maxHp", 0, "Settings/EnemySettings.ini");

    enemyStatus_.attackPower_                = GetPrivateProfileInt("Enemy_Explosion", "attackPower", 0, "Settings/EnemySettings.ini");
    enemyStatus_.attackCooldown_             = GetPrivateProfileInt("Enemy_Explosion", "attackCooldown", 0, "Settings/EnemySettings.ini");
    enemyStatus_.collisionScale_             = GetPrivateProfileFloat("Enemy_Explosion", "collisionScale", 0, "Settings/EnemySettings.ini");

    enemyAlgorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Explosion", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Explosion", "patrolRadius", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Explosion", "approachDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Explosion", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Explosion::~Enemy_Explosion()
{
    // �G�l�~�[�̃}�l�[�W���[���X�g���玀�񂾃G�l�~�[���폜����
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Explosion::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Enemy/Enemy_Explosion.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, anim.startFrame, anim.endFrame, anim.speed);

    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionOffset, enemyStatus_.collisionScale_);
    AddCollider(pCollision);

    // ���f���̉�]
    transform_.rotate_.y = modelRotate.y;


}

void Enemy_Explosion::Update()
{
    // ���ݒn��ۑ�����
    currentPosition_ = transform_.position_;

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
        if (enemyAlgorithm_.attackDistance_ <= CheckPlayerDistance())
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
        // ���łɂ��̓G�ɑ΂��ăq�b�g�ς݂̏ꍇ�͖���
        if (hitEnemies.find(pTarget) != hitEnemies.end()) return;

        // EnemyBase�ɃL���X�g
        BulletBase* pBullet = dynamic_cast<BulletBase*>(pTarget);

        // �_���[�W��^����
        DecreaseHp(pBullet->GetBulletParameter().damage_);

        // �q�b�g���L�^
        hitEnemies.insert(pTarget);

        // �ђʂ��Ȃ��ꍇ�͒e�ۂ�����
        if (pBullet->GetBulletParameter().isPenetration_ == 0) pBullet->KillMe();
    }

    // �G�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        transform_.position_ = currentPosition_;
    }
};

void Enemy_Explosion::Attack()
{
}