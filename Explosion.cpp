#include "Explosion.h"
#include "AudioManager.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "PlayScene.h"

// コンストラクタの実装
Explosion::Explosion(const XMFLOAT3& position, float explodeScale, float damage, float explosionVolume, TargetType targetType)
    : playScene_(nullptr), position_(position), explodeScale_(explodeScale), damage_(damage), explosionVolume_(explosionVolume), targetType_(targetType) {}

// TriggerExplosionメソッドの実装
void Explosion::TriggerExplosion()
{
    // 爆発エフェクトとサウンドを再生
    AudioManager::Play(AUDIO_ID::EXPLODE, explosionVolume_);
    EffectManager::CreateVfx(position_, VFX_TYPE::EXPLODE);

    // ターゲットタイプによって処理を分岐
    if (targetType_ == TargetType::Enemy)
    {
        // エネミーを対象とする場合
        EnemyManager* pEnemyManager = playScene_->GetEnemyManager();

        for (EnemyBase* enemy : pEnemyManager->GetEnemyList())
        {
            XMFLOAT3 enemyPos = enemy->GetPosition();
            float distance = CalculateDistance(position_, enemyPos);
            if (distance <= explodeScale_)
            {
                enemy->DecreaseHp(damage_);
                enemy->BulletHit();
            }
        }
    }
    else if (targetType_ == TargetType::Player)
    {
        // プレイヤーを対象とする場合
        //Player* pPlayer = playScene_->GetPlayer();

        XMFLOAT3 playerPos = pPlayer->GetPosition();
        float distance = CalculateDistance(position_, playerPos);
        if (distance <= explodeScale_)
        {
            pPlayer->DecreaseHp(damage_);
        }
    }
}
