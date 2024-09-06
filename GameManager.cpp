#include "GameManager.h"
#include "AudioManager.h"
#include "EffectManager.h"
#include "Gun.h"
#include "BulletInfoDisplay.h"

namespace GameManager
{	
	Gun* pGun_ = nullptr;

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
		if(pGun_ != nullptr)
		{
			pGun_->GetBulletInfoDisplay()->SetCurrentMagazine(pGun_->GetBulletCount());
			pGun_->GetBulletInfoDisplay()->SetMaxMagazine(pGun_->GetMagPool());
			pGun_->GetBulletInfoDisplay()->DrawBullet();
		}
	}

	void GameManager::Release()
	{
	}

	void SetGun(Gun* gun)
	{
		pGun_ = gun;
	}

	Gun* GetGun()
	{
		return pGun_;
	}

	
}