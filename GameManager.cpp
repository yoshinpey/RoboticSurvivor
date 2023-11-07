#include "GameManager.h"

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
