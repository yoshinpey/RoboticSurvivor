#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"
#include "JsonReader.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };      // �����蔻��̈ʒu
}

//�R���X�g���N�^
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Explosion"), hModel_(-1)
{
    // JSON�t�@�C���ǂݍ���
    JsonReader::Load("Settings/JsonWeaponSettings.json");
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
    hModel_ = Model::Load("Entity/Bullet.fbx");
    assert(hModel_ >= 0);

    //�����蔻��
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);

    //transform_.scale_.x = 5.0f;
    //transform_.scale_.y = 5.0f;
    //transform_.scale_.z = 5.0f;
}

//�X�V
void Bullet_Explosion::Update()
{
    //�e���΂�
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // ��������
    if (parameter_.killTimer_ <= 30)
    {
        transform_.scale_.x *= 1.1;
        transform_.scale_.y *= 1.1;
        transform_.scale_.z *= 1.1;
        pCollision_->SetRadius(transform_.scale_.x);
    }

    //�e������
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) { KillMe(); }
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

void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // ���O�ɃG�l�~�[���܂܂��I�u�W�F�N�g�ɏՓ˂����Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {

        // �ђʂ��Ȃ��ꍇ�͎��g������
        if (parameter_.isPenetration_ == 0) KillMe();
    }
}