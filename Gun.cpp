#include "Engine/Model.h"
#include "AudioManager.h"
#include "InputManager.h"

#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"

#include "Player.h"
#include "JsonReader.h"
#include "BulletInfoDisplay.h"
#include "GameManager.h"

namespace
{
    const XMFLOAT3 handOffset = { 0.6f, -1.25f, 1.50f };      // 移動量
    const XMFLOAT3 modelScale = { 1.0f, 1.0f, 1.0f };         // モデルサイズ
    const std::string modelName = "Model/Rifle.fbx";          // モデル名
    const float Volume = 0.1f;                                // 音量
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), moveDirection_{ 0,0,0 }, pPlayer_(nullptr), pBulletInfoDisplay_(nullptr)
{
    GameManager::SetGun(this);
}

Gun::~Gun()
{
    GameManager::SetGun(nullptr);
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

    pBulletInfoDisplay_ = Instantiate<BulletInfoDisplay>(this);

    // JSONファイルの読み込み
    JsonReader::Load("Settings/WeaponSettings.json");

    // BulletTypeに対応するセクション名を管理するマップ
    std::unordered_map<BulletType, std::string> bulletTypeToSectionName =
    {
        { BulletType::NORMAL, "Bullet_Normal" },
        { BulletType::EXPLOSION, "Bullet_Explosion" }
        // 他の銃弾が追加されたらここに追加
    };

    // 各弾丸タイプの情報を初期化
    for (const auto& pair : bulletTypeToSectionName)
    {
        BulletType type = pair.first;
        std::string sectionName = pair.second;

        // 銃弾ごとの設定を読み込む
        auto& bulletSection = JsonReader::GetSection(sectionName);

        // 射撃間隔の初期化
        bulletInfoList_[(int)type].shotCoolTime_ = bulletSection["shotCoolTime"];
        bulletInfoList_[(int)type].currentShotCoolTime_ = 0;

        // マガジン数の初期化
        bulletInfoList_[(int)type].magSize_ = bulletSection["magSize"];
        bulletInfoList_[(int)type].bulletCount_ = bulletInfoList_[(int)type].magSize_;

        // リロード時間の初期化
        bulletInfoList_[(int)type].reloadTime_ = bulletSection["reloadTime"];
        bulletInfoList_[(int)type].currentReloadTime_ = 0;

        // 待機マガジンの最大数で初期化
        bulletInfoList_[(int)type].magPool_ = bulletSection["magPool"];
    }
}    

void Gun::Update()
{
    // すべての弾丸のクールタイム、リロード時間などをそれぞれ減らす
    for (auto& bullet : bulletInfoList_)
    {
        // 銃一発の射撃間隔を減らす
        if (bullet.currentShotCoolTime_ > 0) bullet.currentShotCoolTime_--;

        // リロード中の場合
        if (bullet.currentReloadTime_ > 0)
        {
            // リロード時間を減らす
            bullet.currentReloadTime_--;

            // リロード時間が終了したら弾を補充する
            if (bullet.currentReloadTime_ <= 0)
            {
                if (bullet.magPool_ <= 0)return;
                if (bullet.magPool_ < bullet.magSize_)
                {
                    bullet.bulletCount_ = bullet.magPool_;
                    bullet.magPool_ = 0;
                    return;
                }
                bullet.magPool_ -= bullet.magSize_ - bullet.bulletCount_;
                
                bullet.bulletCount_ = bullet.magSize_;  // マガジンをリロード
                OutputDebugString("Reload Completed\n");
            }
        }
    }

    // 入力処理
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

    // リロードボタンを押したとき
    if (InputManager::IsReload())
    {
        if (currentMode_ == ShootingMode::NORMAL)
        {
            OutputDebugString("NormalReloading");
            StartReloading(BulletType::NORMAL, AUDIO_ID::CURSOR_POINT);
        }
        else if (currentMode_ == ShootingMode::SPECIAL)
        {
            OutputDebugString("SpecialReloading");
            StartReloading(BulletType::EXPLOSION, AUDIO_ID::CURSOR_POINT);
        }
        return; // リロードが優先されるため、他の入力処理を行わない
    }

    // 通常射撃ボタンを押したとき
    if (InputManager::IsShoot())
    {
        if (currentMode_ != ShootingMode::NORMAL)
        {
            SwitchMode(ShootingMode::NORMAL);  // 通常射撃モードに設定
        }
        HandleShooting<Bullet_Normal>(BulletType::NORMAL, AUDIO_ID::SHOT, AUDIO_ID::CURSOR_POINT);
        return; // 通常射撃と同時に特殊射撃の処理を行うことを防ぐ
    }

    // 特殊射撃ボタンを押したとき
    if (InputManager::IsWeaponAction())
    {
        if (currentMode_ != ShootingMode::SPECIAL)
        {
            SwitchMode(ShootingMode::SPECIAL); // 特殊射撃モードに設定
        }
        HandleShooting<Bullet_Explosion>(BulletType::EXPLOSION, AUDIO_ID::SHOT_EXPLODE, AUDIO_ID::CURSOR_POINT);
    }
}

template <class T>
void Gun::ShootBullet(BulletType type)
{
    // 弾丸の種類に応じたクールタイムを設定
    bulletInfoList_[(int)type].currentShotCoolTime_ = bulletInfoList_[(int)type].shotCoolTime_;

    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");

    // これは高頻度で処理するので、わかりにくいけどFindではなく親をたどって生成（Aim->Player->PlayScene）
    BulletBase* pNewBullet =  Instantiate<T>(GetParent()->GetParent()->GetParent());

    // モデルのボーン位置を元に、射出方向･速度計算する
    moveDirection_ = CalculateBulletMovement(GunTop, GunRoot, pNewBullet->GetBulletParameter().speed_);

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(moveDirection_);
}

template <class T>
void Gun::HandleShooting(BulletType type, AUDIO_ID shotSoundId, AUDIO_ID reloadSoundId)
{
    // リロード中なら射撃を無効化
    if (bulletInfoList_[(int)type].currentReloadTime_ > 0)return;

    // 射撃クール(連射速度を制御する変数)が残っていたら計算しない
    if (bulletInfoList_[(int)type].currentShotCoolTime_ > 0)return;

    // マガジンに弾が残っているとき
    if (bulletInfoList_[(int)type].bulletCount_ > 0)
    {
        AudioManager::Play(shotSoundId, Volume);                         // 発砲音再生
        ShootBullet<T>(type);                                            // 銃弾の生成
        bulletInfoList_[(int)type].bulletCount_--;              //マガジンを減らす
    }
    else if (bulletInfoList_[(int)type].currentReloadTime_ <= 0)
    {
        // マガジンが0になったなら自動でリロード開始
        StartReloading(type, reloadSoundId);
    }
}

// リロード開始
void Gun::StartReloading(BulletType type, AUDIO_ID reloadSoundId)
{
    // 現在の弾数を整数型から文字列型に変換
    OutputDebugString(std::to_string(bulletInfoList_[(int)type].bulletCount_).c_str());
    OutputDebugString("\n");

    bulletInfoList_[(int)type].currentReloadTime_ = bulletInfoList_[(int)type].reloadTime_;
    AudioManager::Play(reloadSoundId, Volume);  // リロード音を再生
}