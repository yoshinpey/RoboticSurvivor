#include "PlayerCharacter.h"
#include "PlayerController.h" // 必要なヘッダファイルをインクルード

PlayerCharacter::PlayerCharacter(GameObject* parent)
    : GameObject(parent, "PlayerCharacter")
{
}

void PlayerCharacter::Initialize()
{
    // プレイヤーキャラクターの初期化処理を記述
}

void PlayerCharacter::Update()
{
    // プレイヤーキャラクターの更新処理を記述
}

void PlayerCharacter::Draw()
{
    // プレイヤーキャラクターの描画処理を記述
}

void PlayerCharacter::Release()
{
    // プレイヤーキャラクターの解放処理を記述
}
