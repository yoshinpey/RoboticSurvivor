#include "GameManager.h"

GameManager::GameManager(GameObject* parent)
    : GameObject(parent, "GameManager")
{
    gameMode = GAME_MODE_NORMAL;
}

void GameManager::Initialize()
{
    // ゲーム全般の初期化処理を記述
}

void GameManager::Update()
{
    // ゲーム全般の更新処理を記述
}

void GameManager::Draw()
{
    // ゲーム全般の描画処理を記述
}

void GameManager::Release()
{
    // ゲーム全般のリソース解放処理を記述
}

GAME_MODE GameManager::GetGameMode() const
{
    return gameMode;
}

void GameManager::SetGameMode(GAME_MODE mode)
{
    gameMode = mode;
    // ゲームモードが切り替わった際の処理を記述
}
