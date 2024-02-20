#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"


//�R���X�g���N�^
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Explosion"), hModel_(-1)
{
    parameter_.damage_ = GetPrivateProfileFloat("Bullet_Explosion", "damage", 0, "Settings/WeaponSettings.ini");
    parameter_.shotCoolTime_ = GetPrivateProfileFloat("Bullet_Explosion", "shotCoolTime", 0, "Settings/WeaponSettings.ini");
    parameter_.speed_ = GetPrivateProfileFloat("Bullet_Explosion", "speed", 0, "Settings/WeaponSettings.ini");
    parameter_.killTimer_ = GetPrivateProfileFloat("Bullet_Explosion", "killTimer", 0, "Settings/WeaponSettings.ini");
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
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.0f);
    AddCollider(collision);
}

//�X�V
void Bullet_Explosion::Update()
{
    //�e���΂�
    transform_.position_ = CalculateFloat3Add(transform_.position_, GetMove());

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
        pTarget->KillMe();
    }
}