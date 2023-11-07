#pragma once
#include "Engine/GameObject.h"

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
