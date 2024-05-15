#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"
#include "JsonReader.h"
#include "Gun.h"
#include "AudioManager.h"
#include "EffectManager.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };    // �����蔻��̈ʒu
    XMFLOAT3 modelScale = { 0.2f, 0.2f, 0.2f };         // ���f���̃T�C�Y
    std::string modelName = "Entity/Missile.fbx";       // ���f����

    //////////////////////////////
    const float gravity = -0.0025f;          // �d��
    const float accelerationLimit = -0.3f;  // �������E
}

//�R���X�g���N�^
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::EXPLOSION, "Bullet_Explosion"), hModel_(-1), pGun_(nullptr), 
    isFirstHit_(true), gravity_(gravity), verticalSpeed_(0.0f)
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
    parameter_.isPenetration_ = bullet_explosion["isPenetration"];
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
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);

    pGun_ = static_cast<Gun*>(FindObject("Gun"));
}

//�X�V
void Bullet_Explosion::Update()
{
    // �����x����
    if(verticalSpeed_ >= accelerationLimit) verticalSpeed_ += gravity_;
    
    // �ʒu��ۑ�����
    XMFLOAT3 prePos = transform_.position_;

    // �d�͂����Z���ĕ������^��������
    transform_.position_.y += verticalSpeed_;

    // �e�N���X�ł��炩���ߌv�Z���Ă�������(�e���̐�)�֔�΂�
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // ���f���̌��������킹��
    XMFLOAT3 targetVector = CalculateFloat3Sub(transform_.position_, prePos);
    RotateToTarget(targetVector);

    // ��������
    if (parameter_.killTimer_ <= 0)
    { 
        AudioManager::Play(AudioManager::AUDIO_ID::EXPLODE);
        EffectManager::CreateVfx(transform_.position_, VFX_TYPE::EXPLODE);
        pCollision_->SetRadius(parameter_.collisionScale_*20.0f);
        KillMe(); 
    }

    //�e������
    parameter_.killTimer_--;
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
    targetVector = NormalizeFloat3(targetVector);

    XMFLOAT3 rot = XMFLOAT3();
    rot.x = XMConvertToDegrees(asinf(targetVector.y));
    rot.y = XMConvertToDegrees(atan2f(targetVector.x, targetVector.z)) + 180.0f;
    transform_.rotate_ = rot;
}


void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // �n�ʊ֘A�̕��̂ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Stage") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
    // �G�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
};