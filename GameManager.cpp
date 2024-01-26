#include "GameManager.h"

#include "EnemyManager.h"


namespace GameManager
{	
	GameObject* pGameObject_ = nullptr;
	EnemyManager* pEnemyManager_ = nullptr;


	void GameManager::Initialize(GameObject* gameObject)
	{
		pGameObject_ = gameObject;
		pEnemyManager_ = new EnemyManager(pGameObject_);
	}

	void GameManager::Update()
	{

	}

	void GameManager::Release()
	{
		SAFE_DELETE(pEnemyManager_);
	}

	GameObject* GetGameObject(){return pGameObject_;}
	EnemyManager* GetEnemyManager() { return pEnemyManager_; }
}