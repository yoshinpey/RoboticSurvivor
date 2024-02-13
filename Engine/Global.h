#pragma once
#include "Direct3D.h"

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// �����x�N�g��
static constexpr XMFLOAT3 UP_VECTOR = { 0.0f, 1.0f, 0.0f };
static constexpr XMFLOAT3 DOWN_VECTOR = { 0.0f, -1.0f, 0.0f };
static constexpr XMFLOAT3 RIGHT_VECTOR = { 1.0f, 0.0f, 0.0f };
static constexpr XMFLOAT3 LEFT_VECTOR = { -1.0f, 0.0f, 0.0f };
static constexpr XMFLOAT3 FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };
static constexpr XMFLOAT3 BACKWARD_VECTOR = { 0.0f, 0.0f, -1.0f };

// 1�x�x�N�g���ɕϊ���������SIMD���Z(�������Z)�����p�ł��邽�ߌ����I�炵��
// �ȉ��A�e��v�Z�֐�

// �n����XMFLOAT3�����̂܂ܐ��K������֐�
static void NormalizeFloat3(XMFLOAT3& vec)
{
    XMVECTOR v = XMVector3Normalize(XMLoadFloat3(&vec));
    XMStoreFloat3(&vec, v);
}

// XMFLOAT3�̉��Z
// �߂�l = a + b
static XMFLOAT3 CalculateFloat3Add(const XMFLOAT3& a, const XMFLOAT3& b)
{
    XMFLOAT3 result = {0,0,0};
    XMStoreFloat3(&result, XMVectorAdd(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3�̌��Z
// �߂�l = a - b
static XMFLOAT3 CalculateFloat3Sub(const XMFLOAT3& a, const XMFLOAT3& b)
{
    XMFLOAT3 result = { 0,0,0 };
    XMStoreFloat3(&result, XMVectorSubtract(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3�^��2�_�ԋ������v�Z����֐� 
// �߂�l = |point2 - point1|
static float CalculateDistance(const XMFLOAT3& point1, const XMFLOAT3& point2)
{
    // �x�N�g���̒������v�Z���ċ������擾
    return XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&point2), XMLoadFloat3(&point1))));
}

// XMFLOAT3�^��2�_��������x�N�g�����v�Z����֐�
// �߂�l = �|�C���g1����|�C���g2�֌����������x�N�g��
static XMFLOAT3 CalculateDirection(const XMFLOAT3& point1, const XMFLOAT3& point2)
{
    // XMVECTOR��XMFLOAT3�ɕϊ����ĕԂ�
    XMFLOAT3 direction;
    XMStoreFloat3(&direction, XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&point2), XMLoadFloat3(&point1))));
    return direction;
}

// INI�t�@�C������float���擾����֐�
static float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    // �t�@�C����
    TCHAR buffer[MAX_PATH];

    // ��������擾
    DWORD result = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);
    
    // �����񂪎擾�ł�����float�ɕϊ����Ēl��Ԃ�
    if (result != 0) return static_cast<float>(atof(buffer));
    else return static_cast<float>(atof(lpDefault));
}
