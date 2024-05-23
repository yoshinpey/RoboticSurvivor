#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Normal.h"

#include "JsonReader.h"
//#include "AudioManager.h"
//#include "EffectManager.h"
#include "Character.h"

namespace
{
    const XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };        // �����蔻��̈ʒu
    const std::string modelName = "Entity/Bullet.fbx";            // ���f����
}

//�R���X�g���N�^
Bullet_Normal::Bullet_Normal(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Normal"), hModel_(-1)
{
    // JSON�t�@�C���ǂݍ���
    JsonReader::Load("Settings/WeaponSettings.json");
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

    // �e�̐������ԏ���
    if (parameter_.killTimer_ > 0) parameter_.killTimer_--;    // �e�̐����^�C�}�[�����炷
    else KillMe();
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
    // �n�ʊ֘A�̕��̂ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Stage") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }

    // �G�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // ���łɂ��̓G�ɑ΂��ăq�b�g�ς݂̏ꍇ�͖���
        if (hitEnemies.find(pTarget) != hitEnemies.end()) return;

        // Character�ɃL���X�g
        Character* pCharacter = dynamic_cast<Character*>(pTarget);

        // �_���[�W��^����
        pCharacter->DecreaseHp(parameter_.damage_);

        // �ђʂ��Ȃ��ꍇ�͒e�ۂ�����.�ђʂ���ꍇ�̓q�b�g���L�^
        if (parameter_.isPenetration_ == 0)  parameter_.killTimer_ = 0;     
        else hitEnemies.insert(pTarget);
    }
}
