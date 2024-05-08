#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"
#include "JsonReader.h"
#include "Gun.h"
#include "AudioManager.h"


namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };    // �����蔻��̈ʒu
    XMFLOAT3 modelScale = { 0.2f, 0.2f, 0.2f };         // ���f���̃T�C�Y
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };      // ���f���̉�]
    std::vector<std::string> fileName = 
    {
        "Entity/Missile.fbx"
    };
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
    hModel_ = Model::Load(fileName[0]);
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
    ///////////////////////
    
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
    if (parameter_.killTimer_ <= 30)
    { 
        // �����e���̏���
        if (isFirstHit_)
        {
            AudioManager::Play(AudioManager::AUDIO_ID::EXPLODE);
            isFirstHit_ = false;
        }
        transform_.scale_.x *= 1.1f;
        transform_.scale_.y *= 1.1f;
        transform_.scale_.z *= 1.1f;
        pCollision_->SetRadius(transform_.scale_.x);
    }

    //�e������
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) 
    { 
        isFirstHit_ = true;
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
void Bullet_Explosion::RotateToTarget(const XMFLOAT3& targetVector)
{
    // ��������������
    XMVECTOR vTargetVector = -XMVector3Normalize(XMVectorSet(targetVector.x, 0, targetVector.z, 0));

    // ���݌����Ă������
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR rotForward = XMVector3Normalize(XMVectorSet(sinf(rotY), 0, cosf(rotY), 0));

    // ���ςƊO�ς��v�Z
    float dot = XMVectorGetX(XMVector3Dot(rotForward, vTargetVector));
    XMVECTOR cross = XMVector3Cross(rotForward, vTargetVector);

    // �p�x���v�Z���ĉ�]
    float angle = static_cast<float>(atan2(XMVectorGetY(cross), dot));
    transform_.rotate_.y += XMConvertToDegrees(angle);
}


void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // �n�ʊ֘A�̕��̂ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Ground") != std::string::npos)
    {
        parameter_.killTimer_ = 30;
        KillMe();
    }
};