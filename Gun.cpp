#include "Engine/Model.h"

#include "AudioManager.h"
#include "InputManager.h"

#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"

#include "Player.h"
#include "JsonReader.h"

namespace
{
    const XMFLOAT3 handOffset = { 0.6f, -1.25f, 1.50f };      // �ړ���
    const XMFLOAT3 modelScale = { 1.0f, 1.0f, 1.0f };         // ���f���T�C�Y
    const std::string modelName = "Entity/Rifle.fbx";         // ���f����
    const float Volume = 0.1f;                                // ����
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), moveDirection_{ 0,0,0 }, pPlayer_(nullptr)
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

    // �o���b�g�^�C�v��enum�T�C�Y�ŏ�����
    bulletInfoList_.resize(static_cast<int>(BulletType::MAX));

    // �v���C���[�̃|�C���^�擾
    pPlayer_ = static_cast<Player*>(FindObject("Player"));

    // JSON�t�@�C���̓ǂݍ���
    JsonReader::Load("Settings/WeaponSettings.json");

    // BulletType�ɑΉ�����Z�N�V���������Ǘ�����n�b�V���}�b�v
    std::unordered_map<BulletType, std::string> bulletTypeToSectionName = {
        { BulletType::NORMAL, "Bullet_Normal" },
        { BulletType::EXPLOSION, "Bullet_Explosion" }
        // ����BulletType���ǉ����ꂽ�炱���ɒǉ�
    };

    // �e�e�ۃ^�C�v�̏���������
    for (int i = 0; i < static_cast<int>(BulletType::MAX); ++i)
    {
        BulletType type = static_cast<BulletType>(i);
        bulletInfoList_[i].coolTime_ = 0;

        // �e�e���Ƃ̐ݒ��ǂݍ���
        auto it = bulletTypeToSectionName.find(type);
        if (it != bulletTypeToSectionName.end())
        {
            auto& bulletSection = JsonReader::GetSection(it->second);

            bulletInfoList_[i].magazineSize_ = bulletSection["magazineSize"];
            bulletInfoList_[i].reloadTime_ = bulletSection["reloadTime"];
            bulletInfoList_[i].magazineCount_ = bulletInfoList_[i].magazineSize_;
            bulletInfoList_[i].currentReloadTime_ = 0;
        }
    }
}    

void Gun::Update()
{
    // ���ׂĂ̒e�ۂ̃N�[���^�C���ƁA�����[�h���ԂȂǂ����ꂼ�ꌸ�炷
    for (auto& bullet : bulletInfoList_)
    {
        bullet.coolTime_--;
        if (bullet.currentReloadTime_ > 0)
        {
            bullet.currentReloadTime_--;
            if (bullet.currentReloadTime_ == 0)
            {
                bullet.magazineCount_ = bullet.magazineSize_; // �����[�h����
            }
        }
    }
    InputConfirmation();

}

void Gun::Draw()
{

    bool shouldDraw = true;

    if (pPlayer_->IsInvincible())
    {
        flickerTimer_++;

        // �_�ł̊Ԋu�����߂�i�����ł�10�t���[�����Ƃɓ_�Łj
        if (flickerTimer_ % 20 >= 10)shouldDraw = false;
    }
    else
    {
        // ���G���ԂłȂ��ꍇ�A�^�C�}�[�����Z�b�g
        flickerTimer_ = 0;
    }

    if (shouldDraw)
    {
        // �e�͏�Ɏ�O�ɕ\���������̂ŁA�[�x�o�b�t�@�������݂��ꎞ�����ɂ���
        // ��������Εǂ�n�ʂɖ��܂�Ȃ�
        Direct3D::SetDepthBafferWriteEnable(false);
        Model::SetTransform(hModel_, transform_);
        Model::Draw(hModel_);
        Direct3D::SetDepthBafferWriteEnable(true);
    }
}

void Gun::Release()
{
}

XMFLOAT3 Gun::CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed)
{
    // �ˏo�������v�Z���Đ��K�������x���|����  (top - root) * speed
    XMVECTOR vMove = XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root))) * bulletSpeed;

    // XMFLOAT3�^�ɖ߂�
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}

void Gun::InputConfirmation()
{
    // ���G���Ԓ��͍U��������
    if (pPlayer_->IsInvincible())return;

    // �ʏ�ˌ�
    if (InputManager::IsShoot() && bulletInfoList_[(int)BulletType::NORMAL].coolTime_ <= 0)
    {
        if (bulletInfoList_[(int)BulletType::NORMAL].magazineCount_ > 0)
        {
            AudioManager::Play(AUDIO_ID::SHOT, Volume);
            ShootBullet<Bullet_Normal>(BulletType::NORMAL);
            bulletInfoList_[(int)BulletType::NORMAL].magazineCount_--;
        }
        else if (bulletInfoList_[(int)BulletType::NORMAL].currentReloadTime_ == 0)
        {
            StartReloading(BulletType::NORMAL);
        }
    }

    // ����ˌ�
    if (InputManager::IsWeaponAction() && bulletInfoList_[(int)BulletType::EXPLOSION].coolTime_ <= 0)
    {
        if (bulletInfoList_[(int)BulletType::EXPLOSION].magazineCount_ > 0)
        {
            AudioManager::Play(AUDIO_ID::SHOT_EXPLODE, Volume);
            ShootBullet<Bullet_Explosion>(BulletType::EXPLOSION);
            bulletInfoList_[(int)BulletType::EXPLOSION].magazineCount_--;
        }
        else if (bulletInfoList_[(int)BulletType::EXPLOSION].currentReloadTime_ == 0)
        {
            StartReloading(BulletType::EXPLOSION);
        }
    }
}

template <class T>
void Gun::ShootBullet(BulletType type)
{
    // ����͍��p�x�ŏ�������̂ŁA�킩��ɂ�������Find�ł͂Ȃ��e�����ǂ��Đ����iAim->Player->PlayScene�j
    BulletBase* pNewBullet = Instantiate<T>(GetParent()->GetParent()->GetParent());

    // �e�ۂ̎�ނɉ������N�[���^�C����ݒ�
    bulletInfoList_[(int)type].coolTime_ = pNewBullet->GetBulletParameter().shotCoolTime_;

    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");

    // ���f���̃{�[���ʒu�����ɁA�ˏo��������x�v�Z����
    moveDirection_ = CalculateBulletMovement(GunTop, GunRoot, pNewBullet->GetBulletParameter().speed_);

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(moveDirection_);
}

// �����[�h�J�n
void Gun::StartReloading(BulletType type)
{
    bulletInfoList_[(int)type].currentReloadTime_ = bulletInfoList_[(int)type].reloadTime_;

    // �����Ń����[�h���̉��A�G�t�F�N�g���Đ�
}