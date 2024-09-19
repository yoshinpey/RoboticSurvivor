
#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Player;
class BulletInfoDisplay;
enum class BulletType;
enum  AUDIO_ID;

// 銃の射撃モード
enum class ShootingMode
{
    NORMAL = 0,
    EXPLODE
};

// バレットの情報を保管する構造体
struct BulletInfo
{
    int shotCoolTime_;                  // 射撃間隔最大値
    int currentShotCoolTime_;           // 射撃間隔保存用

    int reloadTime_;                // リロード時間最大値
    int currentReloadTime_;         // 現在のリロード時間保存用


    int magSize_;                   // マガジン最大値
    int bulletCount_;               // 現在の装弾数

    int magPool_;                   // 待機マガジンに含まれる弾丸の合計数
};

//銃を管理するクラス
class Gun : public GameObject
{
    int hModel_;                    // モデル番号
    XMFLOAT3 moveDirection_;        // 動く方向
    Player* pPlayer_;
    // バレットのリスト
    std::vector<BulletInfo> bulletInfoList_;

    int flickerTimer_;              // 無敵状態のちらつきタイマー
    ShootingMode currentMode_;      // 現在の射撃モード
    BulletType currentBulletType_;  // 現在の弾の種類（モードに依存）
    BulletInfoDisplay* pBulletInfoDisplay_;

public:
    Gun(GameObject* parent);
    ~Gun() override;
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // 銃弾の速度と射出方向を計算する
    XMFLOAT3 CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed);

    // 銃弾を生成する
    template<class T>
    void ShootBullet(BulletType type);

    // 銃を撃つ処理
    // 引数：種類、射撃音、リロード音
    template<class T>
    void HandleShooting(BulletType type, AUDIO_ID shotSoundId, AUDIO_ID reloadSoundId);

    // 移動方向取得
    XMFLOAT3 GetMoveDirection() const { return moveDirection_; }

    // 入力の確認
    void InputConfirmation();

    // リロードを行う
    void StartReloading(BulletType type, AUDIO_ID reloadSoundId);

    // モード切り替えのメソッド
    void SwitchMode(ShootingMode mode) { currentMode_ = mode; }

    BulletInfoDisplay* GetBulletInfoDisplay() { return pBulletInfoDisplay_; }

    int GetBulletCount() { return bulletInfoList_.at((int)currentMode_).bulletCount_; }
    int GetMagPool() { return bulletInfoList_.at((int)currentMode_).magPool_; }

};
