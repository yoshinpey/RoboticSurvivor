#include "Enemy_Fly.h"
#include "EnemyManager.h"
#include "GameManager.h"

//コンストラクタ
Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY), hModel_(-1)
{
    // プレイヤーのステータスを設定
    //characterStatus_.SetCharacterStatus(MAX_HP, ATK);
    //characterStatus_.SetMovementParameters(JUMP_HEIGHT, WALK_SPEED, RUN_SPEED);

}

//デストラクタ
Enemy_Fly::~Enemy_Fly()
{
}

//初期化
void Enemy_Fly::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Character/Enemy.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    pEnemyManager_ = GameManager::GetEnemyManager();
    transform_.position_ = pEnemyManager_->GetSpawnPosition_();
}

//更新
void Enemy_Fly::Update()
{
}

//描画
void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Enemy_Fly::Release()
{
}