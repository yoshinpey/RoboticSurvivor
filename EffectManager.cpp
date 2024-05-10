#include "EffectManager.h"
#include "Engine/VFX.h"

namespace EffectManager
{
	EmitterData sparks;
	EmitterData explodes;
}

void EffectManager::Initialize()
{
	//‰Î‚Ì•²
	sparks.textureFileName = "Particle/cloudA.png";
	sparks.delay = 0;
	sparks.number = 20;
	sparks.lifeTime = 50;
	sparks.directionRnd = XMFLOAT3(90.0f, 90.0f, 90.0f);
	sparks.speed = 0.2f;
	sparks.speedRnd = 1.0f;
	sparks.accel = 0.9f;
	sparks.size = XMFLOAT2(0.3f, 0.3f);
	sparks.sizeRnd = XMFLOAT2(0.1f, 0.1f);
	sparks.scale = XMFLOAT2(0.97f, 0.97f);
	sparks.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
	sparks.deltaColor = XMFLOAT4(0.0f, 0.0f, 0.0f, -1.0f / sparks.lifeTime);
	sparks.gravity = 0.001f;

	//”š”­
	explode.textureFileName = "Particle/cloudA.png";
	explode.delay = 0;
	explode.number = 4;
	explode.lifeTime = 20;
	explode.position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	explode.positionRnd = XMFLOAT3(0.5f, 0.0f, 0.5f);
	explode.direction = XMFLOAT3(1.0f, 1.0f, 1.0f);
	explode.directionRnd = XMFLOAT3(90.0f, 90.0f, 90.0f);
	explode.speed = 0.1f;
	explode.speedRnd = 0.8f;
	explode.size = XMFLOAT2(1.2f, 1.2f);
	explode.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	explode.scale = XMFLOAT2(1.05f, 1.05f);
	explode.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
	explode.deltaColor = XMFLOAT4(0.0f, -1.0f / 20.0f, 0.0f, -1.0f / 20.0f);
	explode.gravity = 0.001f;

	//‰Î‚Ì•²
	dataExp_.textureFileName = "Particle/missilePar.png";
	dataExp_.position = transform_.position_;
	dataExp_.delay = 0;
	dataExp_.number = 1;
	dataExp_.lifeTime = 60;
	dataExp_.positionRnd = XMFLOAT3(0.5f, 0.0f, 0.5f);
	dataExp_.direction = XMFLOAT3(0.0f, 1.0f, 0.0f);
	dataExp_.directionRnd = XMFLOAT3(90.0f, 90.0f, 90.0f);
	dataExp_.speed = 0.1f;
	dataExp_.speedRnd = 1.0f;
	dataExp_.accel = 0.93f;
	dataExp_.size = XMFLOAT2(0.4f, 0.4f);
	dataExp_.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	dataExp_.scale = XMFLOAT2(0.9f, 0.9f);
	dataExp_.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
	dataExp_.deltaColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	dataExp_.gravity = 0.003f;


	//”š”­
	EmitterData data;
	data.position = transform_.position_;
	data.textureFileName = "Particle/missilePar.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 3;
	data.lifeTime = 30;
	data.direction = XMFLOAT3(0.0f, 1.0f, 0.0f);
	data.directionRnd = XMFLOAT3(90.0f, 90.0f, 90.0f);
	data.speed = 0.1f;
	data.speedRnd = 0.8f;
	data.size = XMFLOAT2(0.4f, 0.4f);
	data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	data.scale = XMFLOAT2(1.05f, 1.05f);
	data.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
	data.deltaColor = XMFLOAT4(0.0f, -1.0f / 20.0f, 0.0f, -1.0f / 20.0f);
	VFX::Start(data);
}

void EffectManager::CreateVfx(XMFLOAT3 pos, VFX_TYPE type, XMFLOAT3 other)
{
	switch (type)
	{
	case Explode:
		CreateVfxExplode1(pos);
		break;
	default: break;
	}
}