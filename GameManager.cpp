#include "GameManager.h"
#include "AudioManager.h"
#include "EffectManager.h"

namespace GameManager
{	

	void GameManager::Initialize()
	{
		AudioManager::Initialize();
		EffectManager::Initialize();
	}

	void GameManager::Update()
	{
	}

	void GameManager::Draw()
	{
	}

	void GameManager::Release()
	{
	}
}