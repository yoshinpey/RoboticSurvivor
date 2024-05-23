#pragma once
#include <DirectXMath.h>
using namespace DirectX;

enum class VFX_TYPE 
{
	EXPLODE = 0,
	MAX
};

namespace EffectManager
{
	// エフェクトデータの初期化
	void Initialize();

	// エフェクトを出す
	// 引数：座標, 種類
	void CreateVfx(XMFLOAT3 pos, VFX_TYPE type);
};