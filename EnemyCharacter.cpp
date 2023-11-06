#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(GameObject* parent)
    : GameObject(parent, "EnemyCharacter")
{
}

void EnemyCharacter::Initialize()
{
    // EnemyCharacterの初期化処理をここに記述
}

void EnemyCharacter::Update()
{
    // 敵の行動を制御
}

void EnemyCharacter::Draw()
{
    // 敵の描画
}

void EnemyCharacter::Release()
{
    // 敵キャラクターのリソース解放処理
}
