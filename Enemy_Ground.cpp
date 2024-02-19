#include "Enemy_Ground.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr)
{
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
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // �����蔻��t�^
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 2.0f);
    AddCollider(pCollision_);

#if 0
    /*
    �\���̊ۂ��Ǝ擾�ł���͂��Ȃ̂ɏ�肭�����Ȃ�
    BOOL GetPrivateProfileStruct(
      [in]  LPCTSTR lpszSection,        // �������t�@�C�����̃Z�N�V�����̖��O�B
      [in]  LPCTSTR lpszKey,            // �f�[�^���擾����L�[�̖��O�B
      [out] LPVOID  lpStruct,           // �t�@�C���A�Z�N�V�����A����уL�[���Ɋ֘A�t����ꂽ�f�[�^���󂯎��o�b�t�@�[�ւ̃|�C���^�[�B
      [in]  UINT    uSizeStruct,        // lpStruct �p�����[�^�[���w���o�b�t�@�[�̃T�C�Y (�o�C�g�P��)�B
      [in]  LPCTSTR szFile              // �������t�@�C���̖��O�B
    );

    �߂�l
    �����F0�ȊO
    ���s�F0
    */

    // INI�t�@�C������f�[�^���\���̂֗�������
    GetPrivateProfileStruct("Enemy_Ground_status", "", &status_, sizeof(EnemyStatus), "Settings/EnemySettingsStruct.ini");
    GetPrivateProfileStruct("Enemy_Ground_algorithm", "", &algorithm_, sizeof(EnemyAlgorithm), "Settings/EnemySettingsStruct.ini");
    
#else
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_ = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_ = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
#endif
}

void Enemy_Ground::Update()
{
#if 0
    OutputDebugStringA(("walkSpeed: " + std::to_string(status_.walkSpeed_) + "\n").c_str());
    transform_.position_.x += status_.walkSpeed_;

    OutputDebugStringA(("Size of EnemyStatus: " + std::to_string(sizeof(status_)) + "\n").c_str());
#endif
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
