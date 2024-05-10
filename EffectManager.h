#pragma once
#include <DirectXMath.h>
using namespace DirectX;

enum VFX_TYPE 
{
	SPARK = 0,
	EXPLODE,
};

namespace EffectManager
{
	// VFXデータの初期化
	void Initialize();

	// Typeで指定して生成
	void CreateVfx(XMFLOAT3 pos, VFX_TYPE type, XMFLOAT3 other = XMFLOAT3());
};