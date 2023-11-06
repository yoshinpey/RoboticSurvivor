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

    // ���̃Q�[���S�ʂ̐ݒ��Ǘ����\�b�h��ǉ�

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
    // �Q�[���S�ʂ̏������������L�q
}

void GameManager::Update()
{
    // �Q�[���S�ʂ̍X�V�������L�q
}

void GameManager::Draw()
{
    // �Q�[���S�ʂ̕`�揈�����L�q
}

void GameManager::Release()
{
    // �Q�[���S�ʂ̃��\�[�X����������L�q
}

GAME_MODE GameManager::GetGameMode() const
{
    return gameMode;
}

void GameManager::SetGameMode(GAME_MODE mode)
{
    gameMode = mode;
    // �Q�[�����[�h���؂�ւ�����ۂ̏������L�q
}
