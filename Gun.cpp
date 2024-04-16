
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "InputManager.h"
#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"
#include "Engine/Audio.h"

namespace
{
    XMFLOAT3 handOffset = { 0.6f, -1.25f, 1.50f };       // �ړ���
    XMFLOAT3 modelScale = { 1.0f, 1.0f, 1.0f };         // ���f���T�C�Y
    std::string modelName = "Entity/Rifle.fbx";         // ���f����
    std::string soundName = "Sounds/Shot.wav";          // �T�E���h��
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), normalShotCool_(0), explosionShotCool_(0), hSound_(-1)
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

    hSound_ = Audio::Load(soundName, false, 3);
    assert(hSound_ >= 0);

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
        Audio::Play(hSound_,0.2);
        ShootBullet<Bullet_Normal>();
        normalShotCool_ = shotCoolTime_;
    }
    else
    {
        Audio::Stop(hSound_);
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
    BulletBase* pNewBullet = Instantiate<T>(GetParent()->GetParent()->GetParent());
    float bulletSpeed = pNewBullet->GetBulletParameter().speed_;
    shotCoolTime_ = pNewBullet->GetBulletParameter().shotCoolTime_;

    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
    XMFLOAT3 move = CalculateBulletMovement(GunTop, GunRoot, bulletSpeed);

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(move);
}