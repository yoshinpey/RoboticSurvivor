#pragma once
#include "global.h"
#include "GameObject.h"

enum GAME_MODE
{
    GAME_MODE_NORMAL,
    GAME_MODE_DEBUG,
};

class GameManager : public GameObject
{
public:
    GameManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    GAME_MODE GetGameMode() const;
    void SetGameMode(GAME_MODE mode);

    // 他のゲーム全般の設定や管理メソッドを追加

private:
    GAME_MODE gameMode;
};

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
