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
    const XMFLOAT3 handOffset = { 0.6f, -1.25f, 1.50f };      // 移動量
    const XMFLOAT3 modelScale = { 1.0f, 1.0f, 1.0f };         // モデルサイズ
    const std::string modelName = "Entity/Rifle.fbx";         // モデル名
    const float Volume = 0.1f;                                // 音量
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
    // データのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    //プレイヤーの手の位置まで調整
    transform_.position_ = handOffset;
    transform_.scale_ = modelScale;

    // バレットタイプのenumサイズで初期化
    bulletInfoList_.resize(static_cast<int>(BulletType::MAX));

    // プレイヤーのポインタ取得
    pPlayer_ = static_cast<Player*>(FindObject("Player"));

    // JSONファイルの読み込み
    JsonReader::Load("Settings/WeaponSettings.json");

    // BulletTypeに対応するセクション名を管理するハッシュマップ
    std::unordered_map<BulletType, std::string> bulletTypeToSectionName = {
        { BulletType::NORMAL, "Bullet_Normal" },
        { BulletType::EXPLOSION, "Bullet_Explosion" }
        // 他のBulletTypeが追加されたらここに追加
    };

    // 各弾丸タイプの情報を初期化
    for (int i = 0; i < static_cast<int>(BulletType::MAX); ++i)
    {
        BulletType type = static_cast<BulletType>(i);
        bulletInfoList_[i].coolTime_ = 0;

        // 銃弾ごとの設定を読み込む
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
    // すべての弾丸のクールタイムと、リロード時間などをそれぞれ減らす
    for (auto& bullet : bulletInfoList_)
    {
        bullet.coolTime_--;
        if (bullet.currentReloadTime_ > 0)
        {
            bullet.currentReloadTime_--;
            if (bullet.currentReloadTime_ == 0)
            {
                bullet.magazineCount_ = bullet.magazineSize_; // リロード完了
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

        // 点滅の間隔を決める（ここでは10フレームごとに点滅）
        if (flickerTimer_ % 20 >= 10)shouldDraw = false;
    }
    else
    {
        // 無敵時間でない場合、タイマーをリセット
        flickerTimer_ = 0;
    }

    if (shouldDraw)
    {
        // 銃は常に手前に表示したいので、深度バッファ書き込みを一時無効にする
        // こうすれば壁や地面に埋まらない
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
    // 射出方向を計算して正規化し速度を掛ける  (top - root) * speed
    XMVECTOR vMove = XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root))) * bulletSpeed;

    // XMFLOAT3型に戻す
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}

void Gun::InputConfirmation()
{
    // 無敵時間中は攻撃無効化
    if (pPlayer_->IsInvincible())return;

    // 通常射撃
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

    // 特殊射撃
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
    // これは高頻度で処理するので、わかりにくいけどFindではなく親をたどって生成（Aim->Player->PlayScene）
    BulletBase* pNewBullet = Instantiate<T>(GetParent()->GetParent()->GetParent());

    // 弾丸の種類に応じたクールタイムを設定
    bulletInfoList_[(int)type].coolTime_ = pNewBullet->GetBulletParameter().shotCoolTime_;

    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");

    // モデルのボーン位置を元に、射出方向･速度計算する
    moveDirection_ = CalculateBulletMovement(GunTop, GunRoot, pNewBullet->GetBulletParameter().speed_);

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(moveDirection_);
}

// リロード開始
void Gun::StartReloading(BulletType type)
{
    bulletInfoList_[(int)type].currentReloadTime_ = bulletInfoList_[(int)type].reloadTime_;

    // ここでリロード中の音、エフェクトを再生
}