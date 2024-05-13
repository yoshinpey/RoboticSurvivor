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
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };      // ���f���̉�]
    std::string modelName = "Entity/Missile.fbx";       // ���f����

    //////////////////////////////
    const float initialVelocity = 0.0f;     // �����x
    const float gravity = -0.003f;          // �d��
    const float accelerationLimit = -0.2f;
}

//�R���X�g���N�^
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::EXPLOSION, "Bullet_Explosion"), hModel_(-1), pGun_(nullptr), 
    isFirstHit_(true), gravity_(gravity), verticalSpeed_(initialVelocity)
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
    transform_.rotate_.y = modelRotate.y;

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

    // �������^��������
    transform_.position_.y += verticalSpeed_;

    // �e�N���X�ł��炩���ߌv�Z���Ă��������֔�΂�
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // ���������킹��
    XMFLOAT3 targetVector= pGun_->GetMoveDirection();
    RotateToTarget(targetVector);

    // ��������
    if (parameter_.killTimer_ <= 0)
    { 
        AudioManager::Play(AudioManager::AUDIO_ID::EXPLODE);
        EffectManager::CreateVfx(transform_.position_, VFX_TYPE::EXPLODE);
        pCollision_->SetRadius(parameter_.collisionScale_*2.0);
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
void Bullet_Explosion::RotateToTarget(const XMFLOAT3& targetVector)
{
    XMFLOAT3 rot = XMFLOAT3();
    rot.x = XMConvertToDegrees(-asinf(targetVector.y));
    rot.y = -XMConvertToDegrees(atan2f(targetVector.x, targetVector.z));

    transform_.rotate_ = rot;
}


void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // �n�ʊ֘A�̕��̂ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Stage") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
};