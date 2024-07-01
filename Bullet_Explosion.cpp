#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"

#include "JsonReader.h"
#include "AudioManager.h"
#include "EffectManager.h"
#include "Character.h"
#include "EnemyBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    const XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };    // �����蔻��̈ʒu
    const XMFLOAT3 modelScale = { 0.2f, 0.2f, 0.2f };         // ���f���̃T�C�Y
    const std::string modelName = "Entity/Missile.fbx";       // ���f����

    const float explosionVolume = 0.1f;

    //////////////////////////////
    const float gravity = -0.0025f;          // �e�e�ɂ�����d��
    const float accelerationLimit = -0.4f;   // �������E
    const int modelRotate = 180;             // ���f����]
}

//�R���X�g���N�^
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::EXPLOSION, "Bullet_Explosion"), hModel_(-1), verticalSpeed_(0.0f)
{
    // JSON�t�@�C���ǂݍ���
    JsonReader::Load("Settings/WeaponSettings.json");
    auto& bullet_explosion = JsonReader::GetSection("Bullet_Explosion");

    // �p�����[�^���擾
    parameter_.damage_ = bullet_explosion["damage"];
    parameter_.shotCoolTime_ = bullet_explosion["shotCoolTime"];
    parameter_.speed_ = bullet_explosion["speed"];
    parameter_.killTimer_ = bullet_explosion["killTimer"];
    parameter_.collisionScale_ = bullet_explosion["collisionScale"];
    explodeScale_ = bullet_explosion["explodeScale"];
    parameter_.magazineSize_ = bullet_explosion["magazineSize"];
    parameter_.reloadTime_ = bullet_explosion["reloadTime"];
}

//�f�X�g���N�^
Bullet_Explosion::~Bullet_Explosion()
{
}

//������
void Bullet_Explosion::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    transform_.scale_ = modelScale;

    //�����蔻��
    AddCollider(new SphereCollider(collisionOffset, parameter_.collisionScale_));
}

//�X�V
void Bullet_Explosion::Update()
{
    // �����x����
    if(verticalSpeed_ >= accelerationLimit) verticalSpeed_ += gravity;
    
    // �ʒu��ۑ�����
    XMFLOAT3 previousPosition = transform_.position_;

    // �d�͂����Z���ĕ������^��������
    transform_.position_.y += verticalSpeed_;

    // �e�N���X�ł��炩���ߌv�Z���Ă�������(�e���̐�)�֔�΂�
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // ���f���̌��������킹��
    XMFLOAT3 targetVector = CalculateDirection(transform_.position_, previousPosition);
    RotateToTarget(targetVector);

    // �e�̐������ԏ���
    if (parameter_.killTimer_ > 0)
    { 
        // �e�̐����^�C�}�[�����炷
        parameter_.killTimer_--;
    }
    else
    {
        // ��������
        AudioManager::Play(AUDIO_ID::EXPLODE, explosionVolume);
        EffectManager::CreateVfx(transform_.position_, VFX_TYPE::EXPLODE);

        // �G�Ƃ̋������v�����A�͈͓���������^�_���[�W
        EnemyManager* pEnemyManager = static_cast<PlayScene*>(FindObject("PlayScene"))->GetEnemyManager();
        // �G�l�~�[���X�g���狗���̏����𖞂����G��T��
        for (EnemyBase* e : pEnemyManager->GetEnemyList())
        {
            XMFLOAT3 enePos = e->GetPosition();
            float dist = CalculateDistance(transform_.position_, enePos);
            if (dist < explodeScale_)
            {
                e->DecreaseHp(parameter_.damage_);
                e->BulletHit();
            }
        }
        KillMe();
    }
}

//�`��
void Bullet_Explosion::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Bullet_Explosion::Release()
{
}

// �e�̌�����Ώە����։�]������
void Bullet_Explosion::RotateToTarget(XMFLOAT3& targetVector)
{
    XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f};
    rot.x = XMConvertToDegrees(asinf(targetVector.y));
    rot.y = XMConvertToDegrees(atan2f(targetVector.x, targetVector.z)) + modelRotate;    // ���f���̌����t���������甽�]
    transform_.rotate_ = rot;
}


void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // �G�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
    
    // �n�ʊ֘A�̕��̂ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Stage") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
};