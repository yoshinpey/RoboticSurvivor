#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Normal.h"
#include "JsonReader.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };        // �����蔻��̈ʒu
    std::string modelName = "Entity/Bullet.fbx";            // ���f����
}

//�R���X�g���N�^
Bullet_Normal::Bullet_Normal(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Normal"), hModel_(-1)
{
    // JSON�t�@�C���ǂݍ���
    JsonReader::Load("Settings/JsonWeaponSettings.json");
    auto& bullet_normal = JsonReader::GetSection("Bullet_Normal");

    // �p�����[�^���擾
    parameter_.damage_ = bullet_normal["damage"];
    parameter_.shotCoolTime_ = bullet_normal["shotCoolTime"];
    parameter_.speed_ = bullet_normal["speed"];
    parameter_.killTimer_ = bullet_normal["killTimer"];
    parameter_.collisionScale_ = bullet_normal["collisionScale"];
    parameter_.isPenetration_ = bullet_normal["isPenetration"];
}

//�f�X�g���N�^
Bullet_Normal::~Bullet_Normal()
{
}

//������
void Bullet_Normal::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    //�����蔻��
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);
}

//�X�V
void Bullet_Normal::Update()
{
    //�e���΂�
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    //�e������
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) { KillMe(); }
}

//�`��
void Bullet_Normal::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Bullet_Normal::Release()
{
}

void Bullet_Normal::OnCollision(GameObject* pTarget)
{
    // ���O�ɃG�l�~�[���܂܂��I�u�W�F�N�g�ɏՓ˂����Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        //float damage = DealDamage(parameter_.damage_);
        // �ђʂ��Ȃ��ꍇ�͎��g������
        if (parameter_.isPenetration_ == 0) KillMe();
    }
}