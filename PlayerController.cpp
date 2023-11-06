#include "PlayerController.h"
#include "PlayerCharacter.h" // 必要なヘッダファイルをインクルード

PlayerController::PlayerController(GameObject* parent)
    : GameObject(parent, "PlayerController")
{
}

void PlayerController::Initialize()
{
    // プレイヤーコントローラーの初期化処理を記述
}

void PlayerController::Update()
{
    // プレイヤーコントローラーの更新処理を記述
}

void PlayerController::Release()
{
    // プレイヤーコントローラーのリソース解放処理を記述
}

// プレイヤーの行動を制御するメソッドを追加
