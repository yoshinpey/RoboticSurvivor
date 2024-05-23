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
	// �G�t�F�N�g�f�[�^�̏�����
	void Initialize();

	// �G�t�F�N�g���o��
	// �����F���W, ���
	void CreateVfx(XMFLOAT3 pos, VFX_TYPE type);
};