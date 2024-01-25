#pragma once

class GameObject;
class EnemyManager;

/*
enum class GAME_MODE
{
    NORMAL,
    DEBUG,
};*/

class GameManager
{
private:
    //GAME_MODE gameMode_;
    GameObject* pGameObject_ = nullptr;
    EnemyManager* pEnemyManager_ = nullptr;

public:
    GameManager(GameObject* parent);

    void Initialize();
    void Update();
    void Release();

    //GAME_MODE GetGameMode() const { return gameMode_; }
    //void SetGameMode(GAME_MODE mode){gameMode_ = mode;}
};
