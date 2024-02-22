#include "EnemyState.h"
#include "EnemyBase.h"
#include "StateManager.h"

// 待機状態
EnemyIdleState::EnemyIdleState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyIdleState::EnterState()
{
    // 待機フレーム120をセットする
}

void EnemyIdleState::UpdateState()
{
    // 待機アニメーション再生

    // 待機フレームを減らす。0になったら徘徊状態へ移行

}

void EnemyIdleState::ExitState()
{
}


// 徘徊状態
EnemyWanderingState::EnemyWanderingState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyWanderingState::EnterState()
{
    // 探知間隔フレームをセットする

    /*
    ランダムな移動方向を求める
    戻り値：XMVECTOR 方向

    ランダムな移動距離を求める
    引数：移動範囲(最小移動距離、最大移動距離)
    戻り値：XMVECTOR 移動量
    */
}

void EnemyWanderingState::UpdateState()
{
    // 歩行アニメーション再生

    // 探知間隔フレームが0になった
    /*
    視界にプレイヤーがいるかを判定する
    エネミーの視界にプレイヤーが入っているときは追跡状態へ
    */

    // エネミーの視界にプレイヤーが入っていないとき
    /*
    決められた方向に移動する
    引数：移動量*方向、移動速度
    戻り値：なし、移動処理を行う

    プレイヤーとの距離を計算する
    引数：現在地、目標地
    戻り値：距離

    追跡するかを判定する
    引数：距離、闘値
    戻り値：真 or 偽

    真だったときは追跡状態へ
    */

    // 敵と衝突したら位置を半径分位置をずらす

}

void EnemyWanderingState::ExitState()
{
}


// 追跡状態
EnemyChaseState::EnemyChaseState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyChaseState::EnterState()
{
}

void EnemyChaseState::UpdateState()
{
    // 歩行アニメーション

    /*
    プレイヤーまでの経路を求める
    引数：現在地、目標値

    追跡するかを判定する
    引数：距離、闘値
    戻り値：真 or 偽

    プレイヤーとの距離を計算する
    引数：現在地、目標地
    戻り値：距離
    */

    // 攻撃範囲になったら攻撃状態へ
}

void EnemyChaseState::ExitState()
{
}


// 攻撃状態
EnemyAttackState::EnemyAttackState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyAttackState::EnterState()
{
    // 攻撃クールタイムをセット
}

void EnemyAttackState::UpdateState()
{
    // 攻撃クールタイムを減らす

    // 攻撃クールタイムが0になったら
    // 攻撃アニメーション再生
    // 与ダメージ処理

    // 攻撃範囲を外れたら追跡状態へ

    // 攻撃を受けたら被ダメージステートへ
}

void EnemyAttackState::ExitState()
{
}


// 被ダメージ状態
EnemyDamageState::EnemyDamageState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyDamageState::EnterState()
{
}

void EnemyDamageState::UpdateState()
{
    // 被弾アニメーション再生
    // 被ダメージ処理

    
    // 攻撃を受けたら被弾アニメーションキャンセルを行う
    // 被ダメージステートへ
}

void EnemyDamageState::ExitState()
{
}