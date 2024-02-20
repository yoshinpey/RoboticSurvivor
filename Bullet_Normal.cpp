#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Normal.h"


//�R���X�g���N�^
Bullet_Normal::Bullet_Normal(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Normal"), hModel_(-1)
{
    parameter_.damage_          = GetPrivateProfileFloat("Bullet_Normal", "damage", 0, "Settings/WeaponSettings.ini");
    parameter_.shotCoolTime_    = GetPrivateProfileFloat("Bullet_Normal", "shotCoolTime", 0, "Settings/WeaponSettings.ini");
    parameter_.speed_           = GetPrivateProfileFloat("Bullet_Normal", "speed", 0, "Settings/WeaponSettings.ini");
    parameter_.killTimer_       = GetPrivateProfileFloat("Bullet_Normal", "killTimer", 0, "Settings/WeaponSettings.ini");
}

//�f�X�g���N�^
Bullet_Normal::~Bullet_Normal()
{
}

//������
void Bullet_Normal::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Entity/Bullet.fbx");
    assert(hModel_ >= 0);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.1f);
    AddCollider(collision);
}

//�X�V
void Bullet_Normal::Update()
{
    //�e���΂�
    transform_.position_ = CalculateFloat3Add(transform_.position_, GetMove());

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
        pTarget->KillMe();
    }
}