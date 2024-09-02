#pragma once
#include "Engine/GameObject.h"

class PlayScene;

// ターゲットの種類
enum class TargetType
{
    Enemy,
    Player
};

// 爆発処理クラス
class Explosion
{
private:
    XMFLOAT3 position_;         // 爆発の位置
    float explodeScale_;        // 爆発の範囲
    float damage_;              // ダメージ量
    float explosionVolume_;     // 爆発音の音量
    TargetType targetType_;     // ターゲットの種類（敵かプレイヤーか）
    PlayScene* playScene_;      // PlaySceneへのポインタ

public:
    // コンストラクタ
    Explosion(const XMFLOAT3& position, float explodeScale, float damage, float explosionVolume, TargetType targetType);

    // 爆発を実行するメソッド
    void TriggerExplosion();
};
