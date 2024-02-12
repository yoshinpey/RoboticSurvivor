#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
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

// 正規化
static void NormalizeFloat3(XMFLOAT3& vec)
{
    XMVECTOR v = XMLoadFloat3(&vec);
    v = XMVector3Normalize(v);
    XMStoreFloat3(&vec, v);
}

/*自分用のメモ
名前	意味
LP	    ＊（ポインタ）
C	    const
TSTR	TCHAR(char)
STR	    char
WSTR	WCHAR(ユニコード用：2byte)

定義	正体
LPSTR	char*
LPCSTR	const char*
LPTSTR	TCHAR*
LPCTSTR	const TCHAR*
LPWSTR	WCHAR*
LPCWSTR	const WCHAR*

DWORD  32ビット符号なし整数型
*/

// INIファイルからfloatを取得する関数
static float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    // ファイル名
    TCHAR buffer[MAX_PATH];

    // 文字列を取得
    DWORD result = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);
    
    // 文字列が取得できたらfloatに変換して値を返す
    if (result != 0)return atof(buffer);
    else return atof(lpDefault);
}
