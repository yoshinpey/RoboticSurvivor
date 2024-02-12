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

// INIファイルから浮動小数点数を取得する関数
static float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCSTR lpDefault, LPCTSTR lpFileName)
{
    TCHAR buffer[256];
    GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);

    // 文字列から浮動小数点数に変換
    float result = std::atof(buffer);

    // 変換エラーが発生した場合はデフォルト値を返す
    if (result == 0 && buffer[0] != '0')
    {
        result = std::atof(lpDefault);
    }

    return result;
}
/*
//iniファイルからfloat型の変数を取ってくる
static float GetPrivateProfilefloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    char caption[64];
    int len = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, caption, 64, lpFileName);

    //情報が取れているなら
    if (len)
        return strtof(caption, NULL);   //取った情報を返す
    else
        return strtof(lpDefault, NULL); //Defaultの情報を返す
}
*/
