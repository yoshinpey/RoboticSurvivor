#pragma once
#include <DirectXMath.h>
using namespace DirectX;

enum VFX_TYPE 
{
	EXPLODE = 0,
};

namespace EffectManager
{
	// VFX�f�[�^�̏�����
	void Initialize();

	// Type�Ŏw�肵�Đ���
	void CreateVfx(XMFLOAT3 pos, VFX_TYPE type, XMFLOAT3 other = XMFLOAT3());
};