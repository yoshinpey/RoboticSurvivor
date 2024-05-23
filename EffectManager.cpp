#include "EffectManager.h"
#include "Engine/VFX.h"

namespace EffectManager
{
	///////////////// ”š”­ ////////////////
	EmitterData flame;		// ‰Š
	EmitterData sparks;		// ‰Î‚Ì•²
	EmitterData flash;		// ‘MŒõ
	///////////////////////////////////////
}

void EffectManager::Initialize()
{
	//‰Š
	flame.textureFileName = "Effects/cloudA.png";
	flame.position = XMFLOAT3(0.0f, 0.05f, 0.0f);
	flame.delay = 0;
	flame.number = 50;
	flame.lifeTime = 30;
	flame.direction = XMFLOAT3(0.0f, 1.0f, 0.0f);
	flame.directionRnd = XMFLOAT3(90.0f, 90.0f, 90.0f);
	flame.speed = 0.1f;
	flame.speedRnd = 0.8f;
	flame.size = XMFLOAT2(1.2f, 1.2f);
	flame.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	flame.scale = XMFLOAT2(1.05f, 1.05f);
	flame.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
	flame.deltaColor = XMFLOAT4(0.0f, -1.0f / 20.0f, 0.0f, -1.0f / 20.0f);


	//‰Î‚Ì•²
	sparks.delay = 0;
	sparks.number = 30;
	sparks.lifeTime = 100;
	sparks.positionRnd = XMFLOAT3(0.5f, 0.0f, 0.5f);
	sparks.direction = XMFLOAT3(0.0f, 1.0f, 0.0f);
	sparks.directionRnd = XMFLOAT3(90.0f, 90.0f, 90.0f);
	sparks.speed = 0.25f;
	sparks.speedRnd = 1.0f;
	sparks.accel = 0.93f;
	sparks.size = XMFLOAT2(0.1f, 0.1f);
	sparks.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	sparks.scale = XMFLOAT2(0.99f, 0.99f);
	sparks.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
	sparks.deltaColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	sparks.gravity = 0.003f;

	//’n–Ê
	flash.textureFileName = "Effects/flashA_R.png";
	flash.positionRnd = XMFLOAT3(0.0f, 0.0f, 0.0f);
	flash.isBillBoard = true;
	flash.rotate.x = 0.0f;
	flash.delay = 0;
	flash.number = 1;
	flash.lifeTime = 7;
	flash.speed = 0.0f;
	flash.size = XMFLOAT2(5.0f, 5.0f);
	flash.sizeRnd = XMFLOAT2(0.0f, 0.0f);
	flash.scale = XMFLOAT2(1.25f, 1.25f);
	flash.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.3f);

}

void EffectManager::CreateVfx(XMFLOAT3 pos, VFX_TYPE type)
{
	switch (type)
	{
	case VFX_TYPE::EXPLODE:
		flame.position = pos;
		VFX::Start(flame);
		sparks.position = pos;
		VFX::Start(sparks);
		flash.position = pos;
		VFX::Start(flash);
		break;

	default: 
		break;
	}
}