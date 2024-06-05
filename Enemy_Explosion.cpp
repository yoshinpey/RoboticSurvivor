#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Enemy_Explosion.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"


namespace
{
    const std::string modelName = "Enemy/Enemy_Explosion.fbx";    // ���f����
    const XMFLOAT3 collisionOffset = { 0.0f, 1.0f, 0.0f };        // �����蔻��̈ʒu
    const XMFLOAT3 modelRotate = { 0.0f, 0.0f, 0.0f };            // ���f���̉�]
    const float deltaTime = 0.05f;                                // �_���[�W�̃V�F�[�_�[�̕ω���

    // ���f���̃A�j���[�V����
    struct AnimFrame
    {
        int startFrame = 0;
        int endFrame = 100;
        float speed = 0.75f;
    }anim;
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_                         = GetPrivateProfileFloat("Enemy_Explosion", "maxHp", 0, "Settings/EnemySettings.ini");
    commonStatus_.currentHp_                     = commonStatus_.maxHp_;        // ���݂�HP���ő�l�ŏ�����

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
    // �G�l�~�[�}�l�[�W���[�̃��X�g���玀�񂾃G�l�~�[���폜����
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Explosion::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load(modelName);
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
    pastPosition_ = transform_.position_;

    // �����ꂽ�����܂Ńv���C���[�ɐڋ�
    if (enemyAlgorithm_.attackDistance_ <= CheckPlayerDistance())
    {
        ApproachPlayer(CheckPlayerDirection());
    }

    // �v���C���[�̕����������悤�Ɏ��E����]
    RotateTowardsPlayer(CheckPlayerDirection());
}

void Enemy_Explosion::Draw()
{
    // �_���[�W�V�F�[�_�[�̓K������
    if (damageTime_ > 0) damageTime_ -= deltaTime;
    Direct3D::damageTime = damageTime_;
    
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Direct3D::damageTime = 0.0f;
}

void Enemy_Explosion::Release()
{
}

void Enemy_Explosion::OnCollision(GameObject* pTarget)
{
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        BulletHit();
    }

    // �G�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // �G�l�~�[�x�[�X�ɃL���X�g
        EnemyBase* pEnemy = static_cast<EnemyBase*>(pTarget);
        CollisionDetectionWithEnemy(pEnemy);
    }
};

void Enemy_Explosion::Attack()
{
}