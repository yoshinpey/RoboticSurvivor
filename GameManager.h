#pragma once

class GameObject;

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
    GameObject* pGameObject;

public:
    GameManager(GameObject* parent);

    void Initialize();
    void Update();
    void Release();

    //GAME_MODE GetGameMode() const { return gameMode_; }
    //void SetGameMode(GAME_MODE mode){gameMode_ = mode;}
};
