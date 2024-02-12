#pragma once
#include "Direct3D.h"

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

namespace Constants 
{
    static constexpr XMFLOAT3 UP_VECTOR = { 0.0f, 1.0f, 0.0f };
    static constexpr XMFLOAT3 DOWN_VECTOR = { 0.0f, -1.0f, 0.0f };
    static constexpr XMFLOAT3 RIGHT_VECTOR = { 1.0f, 0.0f, 0.0f };
    static constexpr XMFLOAT3 LEFT_VECTOR = { -1.0f, 0.0f, 0.0f };
    static constexpr XMFLOAT3 FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };
    static constexpr XMFLOAT3 BACKWARD_VECTOR = { 0.0f, 0.0f, -1.0f };
}

// ���K��
static void NormalizeFloat3(XMFLOAT3& vec)
{
    XMVECTOR v = XMLoadFloat3(&vec);
    v = XMVector3Normalize(v);
    XMStoreFloat3(&vec, v);
}

// INI�t�@�C�����畂�������_�����擾����֐�
static float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCSTR lpDefault, LPCTSTR lpFileName)
{
    TCHAR buffer[256];
    GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);

    // �����񂩂畂�������_���ɕϊ�
    float result = std::atof(buffer);

    // �ϊ��G���[�����������ꍇ�̓f�t�H���g�l��Ԃ�
    if (result == 0 && buffer[0] != '0')
    {
        result = std::atof(lpDefault);
    }

    return result;
}
/*
//ini�t�@�C������float�^�̕ϐ�������Ă���
static float GetPrivateProfilefloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    char caption[64];
    int len = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, caption, 64, lpFileName);

    //��񂪎��Ă���Ȃ�
    if (len)
        return strtof(caption, NULL);   //���������Ԃ�
    else
        return strtof(lpDefault, NULL); //Default�̏���Ԃ�
}
*/
