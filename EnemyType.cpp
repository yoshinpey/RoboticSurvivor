#include "EnemyType.h"

EnemyType::EnemyType(GameObject* parent)
    : EnemyCharacter(parent)
{
}

void EnemyType::Initialize()
{
    // EnemyTypeの初期化処理をここに記述
}

void EnemyType::Update()
{
    // 特定の敵の行動を制御
}

void EnemyType::Draw()
{
    // 特定の敵の描画
}

void EnemyType::Release()
{
    // 敵タイプのリソース解放処理
}
