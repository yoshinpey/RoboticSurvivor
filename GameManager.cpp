#include "GameManager.h"

#include "EnemyManager.h"


namespace GameManager
{	
	GameObject* pGameObject_ = nullptr;
	EnemyManager* pEnemyManager_ = nullptr;


	void GameManager::Initialize()
	{
		//pEnemyManager_ = new EnemyManager();
	}

	void GameManager::Update()
	{

	}

	void GameManager::Release()
	{
		SAFE_DELETE(pEnemyManager_);
	}

	EnemyManager* GetEnemyManager() { return pEnemyManager_; }
}