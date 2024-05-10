#include "EffectManager.h"
#include "Engine/VFX.h"

namespace EffectManager
{
	///////////////// ”š”­
	EmitterData flame;		// ‰Š
	EmitterData sparks;		// ‰Î‚Ì•²
	EmitterData flash;		// ‘MŒõ
	/////////////////
}

void EffectManager::Initialize()
{
	//‰Š
	flame.textureFileName = "cloudA.png";
	flame.position = XMFLOAT3(0, 0.05, 0);
	flame.delay = 0;
	flame.number = 80;
	flame.lifeTime = 30;
	flame.direction = XMFLOAT3(0, 1, 0);
	flame.directionRnd = XMFLOAT3(90, 90, 90);
	flame.speed = 0.1f;
	flame.speedRnd = 0.8;
	flame.size = XMFLOAT2(1.2, 1.2);
	flame.sizeRnd = XMFLOAT2(0.4, 0.4);
	flame.scale = XMFLOAT2(1.05, 1.05);
	flame.color = XMFLOAT4(1, 1, 0.1, 1);
	flame.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

	//‰Î‚Ì•²
	sparks.delay = 0;
	sparks.number = 80;
	sparks.lifeTime = 100;
	sparks.positionRnd = XMFLOAT3(0.5, 0, 0.5);
	sparks.direction = XMFLOAT3(0, 1, 0);
	sparks.directionRnd = XMFLOAT3(90, 90, 90);
	sparks.speed = 0.25f;
	sparks.speedRnd = 1;
	sparks.accel = 0.93;
	sparks.size = XMFLOAT2(0.1, 0.1);
	sparks.sizeRnd = XMFLOAT2(0.4, 0.4);
	sparks.scale = XMFLOAT2(0.99, 0.99);
	sparks.color = XMFLOAT4(1, 1, 0.1, 1);
	sparks.deltaColor = XMFLOAT4(0, 0, 0, 0);
	sparks.gravity = 0.003f;

	//’n–Ê
	flash.textureFileName = "flashA_R.png";
	flash.positionRnd = XMFLOAT3(0, 0, 0);
	flash.isBillBoard = false;
	flash.rotate.x = 90;
	flash.delay = 0;
	flash.number = 1;
	flash.lifeTime = 7;
	flash.speed = 0;
	flash.size = XMFLOAT2(5, 5);
	flash.sizeRnd = XMFLOAT2(0, 0);
	flash.scale = XMFLOAT2(1.25f, 1.25f);
	flash.color = XMFLOAT4(1, 1, 1, 0.3f);

}

void EffectManager::CreateVfx(XMFLOAT3 pos, VFX_TYPE type)
{
	switch (type)
	{
	case EXPLODE:
		VFX::Start(flame);
		VFX::Start(sparks);
		VFX::Start(flash);
		break;
	default: break;
	}
}