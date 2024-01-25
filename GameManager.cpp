#include "GameManager.h"
#include "EnemyManager.h"

GameManager::GameManager(GameObject* parent)
	: pGameObject_(parent), pEnemyManager_()
{
	pEnemyManager_ = new EnemyManager(parent); // インスタンス生成
}

void GameManager::Initialize()
{
}

void GameManager::Update()
{
}

void GameManager::Release()
{
}
