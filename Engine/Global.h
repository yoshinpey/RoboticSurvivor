#pragma once
#include "Direct3D.h"

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// 1�x�x�N�g���ɕϊ���������SIMD���Z(�������Z)�����p�ł��邽�ߌ����I�炵��
// �ȉ��A�e��v�Z�֐�

// XMFLOAT3�𐳋K������֐�
// ����:���K��������FLOAT3�^
// �߂�l�F���K������FLOAT3�^
XMFLOAT3 NormalizeFloat3(XMFLOAT3& vec);

// XMFLOAT3�̉��Z
// �߂�l = a + b
XMFLOAT3 CalculateFloat3Add(XMFLOAT3& a, XMFLOAT3& b);

// XMFLOAT3�̌��Z
// �߂�l = a - b
XMFLOAT3 CalculateFloat3Sub(XMFLOAT3& a, XMFLOAT3& b);

// XMFLOAT3�^��2�_�ԋ������v�Z����֐� 
// �߂�l = |point1 - point2|
float CalculateDistance(XMFLOAT3& point1, XMFLOAT3& point2);

// XMFLOAT3�^��2�_��������x�N�g�����v�Z����֐�
// �߂�l = �|�C���g2����|�C���g1�֌����������x�N�g��
XMFLOAT3 CalculateDirection(XMFLOAT3& point1, XMFLOAT3& point2);

// INI�t�@�C������float���擾����֐�
float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName);
