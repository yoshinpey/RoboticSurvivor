#include "Enemy_Ground.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"
#include "Player.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 1.0f, 0.0f };      // �����蔻��̈ʒu
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // ���f���̉�]


    const float deltaTime = 0.05f;                                // �_���[�W�̕\���p�̌o�ߎ���
}

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_ = GetPrivateProfileFloat("Enemy_Ground", "maxHp", 0, "Settings/EnemySettings.ini");
    commonStatus_.currentHp_ = commonStatus_.maxHp_;        // ���݂�HP���ő�l�ŏ�����

    enemyStatus_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    enemyStatus_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    enemyStatus_.collisionScale_             = GetPrivateProfileFloat("Enemy_Ground", "collisionScale", 0, "Settings/EnemySettings.ini");

    enemyAlgorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Ground", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Ground", "patrolRadius", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Ground", "approachDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Ground", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Ground::~Enemy_Ground()
{
    // �G�l�~�[�̃}�l�[�W���[���X�g���玀�񂾃G�l�~�[���폜����
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Ground::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Enemy/Enemy_Ground.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    //Model::SetAnimFrame(hModel_, 0, 120, 0.75);
     
    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionPosition, enemyStatus_.collisionScale_);
    AddCollider(pCollision);

    transform_.rotate_.y = modelRotate.y;

}

void Enemy_Ground::Update()
{    
    // ���ݒn��ۑ�����
    currentPosition_ = transform_.position_;

    // �v���C���[�ւ̕����x�N�g��(���K����)
    XMFLOAT3 directionToPlayer = CheckPlayerDirection();

    // �����ꂽ�����܂Ńv���C���[�ɐڋ�
    if (enemyAlgorithm_.attackDistance_ <= CheckPlayerDistance())
    {
        ApproachPlayer(directionToPlayer);
    }

    // �v���C���[�̕����������悤�Ɏ��E����]
    RotateTowardsPlayer(directionToPlayer);
}

void Enemy_Ground::Draw()
{
    // �_���[�W�V�F�[�_�[�̓K������
    if (damageTime_ > 0) damageTime_ -= deltaTime;
    Direct3D::damageTime = damageTime_;

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Direct3D::damageTime = 0.0f;
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{       
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        damageTime_ = 1.0f;
    }

    // �G�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        //transform_.position_ = currentPosition_;
    }
}

void Enemy_Ground::Attack()
{
}
