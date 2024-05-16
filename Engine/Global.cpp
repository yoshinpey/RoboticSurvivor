#include "Global.h"


// XMFLOAT3�𐳋K������֐�
XMFLOAT3 NormalizeFloat3(XMFLOAT3& vec)
{
    XMVECTOR v = XMVector3Normalize(XMLoadFloat3(&vec));
    XMStoreFloat3(&vec, v);
    return vec;
}

// XMFLOAT3�̉��Z
XMFLOAT3 CalculateFloat3Add(XMFLOAT3& a, XMFLOAT3& b)
{
    XMFLOAT3 result = { 0,0,0 };
    XMStoreFloat3(&result, XMVectorAdd(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3�̌��Z
XMFLOAT3 CalculateFloat3Sub(XMFLOAT3& a, XMFLOAT3& b)
{
    XMFLOAT3 result = { 0,0,0 };
    XMStoreFloat3(&result, XMVectorSubtract(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3�^��2�_�ԋ������v�Z����֐�
float CalculateDistance(XMFLOAT3& point1, XMFLOAT3& point2)
{
    // �x�N�g���̒������v�Z���ċ������擾
    return XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&point1), XMLoadFloat3(&point2))));
}

// XMFLOAT3�^��2�_��������x�N�g�����v�Z����֐�
XMFLOAT3 CalculateDirection(XMFLOAT3& point1, XMFLOAT3& point2)
{
    // XMVECTOR��XMFLOAT3�ɕϊ����ĕԂ�
    XMFLOAT3 direction;
    XMStoreFloat3(&direction, XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&point1), XMLoadFloat3(&point2))));
    return direction;
}

// INI�t�@�C������float���擾����֐�
float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    // �t�@�C����
    TCHAR buffer[MAX_PATH];

    // ��������擾
    DWORD result = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);

    // �����񂪎擾�ł�����float�ɕϊ����Ēl��Ԃ�
    if (result != 0) return static_cast<float>(atof(buffer));
    else return static_cast<float>(atof(lpDefault));
}