
#include "Engine/Model.h"

#include "InputManager.h"
#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"
#include "AudioManager.h"

namespace
{
    XMFLOAT3 handOffset = { 0.6f, -1.25f, 1.50f };       // �ړ���
    XMFLOAT3 modelScale = { 1.0f, 1.0f, 1.0f };         // ���f���T�C�Y
    std::string modelName = "Entity/Rifle.fbx";         // ���f����
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), normalShotCool_(0), explosionShotCool_(0)
{
}

Gun::~Gun()
{
}

void Gun::Initialize()
{
    // �f�[�^�̃��[�h
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    //�v���C���[�̎�̈ʒu�܂Œ���
    transform_.position_ = handOffset;
    transform_.scale_ = modelScale;
}

void Gun::Update()
{
    // �ʏ�ˌ��̃N�[���_�E������
    if (normalShotCool_ > 0) normalShotCool_--;

    // ����ˌ��̃N�[���_�E������
    if (explosionShotCool_ > 0) explosionShotCool_--;

    // �ʏ�ˌ�
    if (InputManager::IsShoot() && normalShotCool_ <= 0)
    {
        AudioManager::Play(AudioManager::AUDIO_ID::SHOT, 0.1f);
        ShootBullet<Bullet_Normal>();
        normalShotCool_ = shotCoolTime_;
    }
    else
    {
        AudioManager::Stop(AudioManager::AUDIO_ID::SHOT);
    }

    // ����ˌ�
    if (InputManager::IsWeaponAction() && explosionShotCool_ <= 0)
    {
        ShootBullet<Bullet_Explosion>();
        explosionShotCool_ = shotCoolTime_;
    }
}

void Gun::Draw()
{
    // �e�͏�Ɏ�O�ɕ\���������̂Ő[�x�𖳎�����
    Direct3D::SetDepthBafferWriteEnable(false);

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // �[�x�ݒ��߂�
    Direct3D::SetDepthBafferWriteEnable(true);
}

void Gun::Release()
{
}

XMFLOAT3 Gun::CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed)
{
    // �ˏo�������v�Z���Đ��K��  (top - root)
    XMVECTOR vMove = XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root)));

    // �e����ǉ��ݒ�(�e�Ɏ�ނ��������Ƃ��p)
    vMove *= bulletSpeed;

    // float3�^�ɖ߂�
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}

template <class T>
void Gun::ShootBullet()
{
    // ����͍��p�x�ŏ�������̂ŁA�킩��ɂ�������Find�ł͂Ȃ��e�����ǂ��Đ����iAim->Player->PlayScene�j
    BulletBase* pNewBullet = Instantiate<T>(GetParent()->GetParent()->GetParent());

    // �p�����[�^�ݒ�
    float bulletSpeed = pNewBullet->GetBulletParameter().speed_;
    shotCoolTime_ = pNewBullet->GetBulletParameter().shotCoolTime_;

    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
    XMFLOAT3 move = CalculateBulletMovement(GunTop, GunRoot, bulletSpeed);
    moveDirection_ = move;

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(move);
}