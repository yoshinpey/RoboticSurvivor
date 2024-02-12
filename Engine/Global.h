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

/*�����p�̃���
���O	�Ӗ�
LP	    ���i�|�C���^�j
C	    const
TSTR	TCHAR(char)
STR	    char
WSTR	WCHAR(���j�R�[�h�p�F2byte)

��`	����
LPSTR	char*
LPCSTR	const char*
LPTSTR	TCHAR*
LPCTSTR	const TCHAR*
LPWSTR	WCHAR*
LPCWSTR	const WCHAR*

DWORD  32�r�b�g�����Ȃ������^
*/

// INI�t�@�C������float���擾����֐�
static float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    // �t�@�C����
    TCHAR buffer[MAX_PATH];

    // ��������擾
    DWORD result = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);
    
    // �����񂪎擾�ł�����float�ɕϊ����Ēl��Ԃ�
    if (result != 0)return atof(buffer);
    else return atof(lpDefault);
}
