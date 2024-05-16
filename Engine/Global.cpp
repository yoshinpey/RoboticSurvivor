#include "Global.h"


// XMFLOAT3を正規化する関数
XMFLOAT3 NormalizeFloat3(XMFLOAT3& vec)
{
    XMVECTOR v = XMVector3Normalize(XMLoadFloat3(&vec));
    XMStoreFloat3(&vec, v);
    return vec;
}

// XMFLOAT3の加算
XMFLOAT3 CalculateFloat3Add(XMFLOAT3& a, XMFLOAT3& b)
{
    XMFLOAT3 result = { 0,0,0 };
    XMStoreFloat3(&result, XMVectorAdd(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3の減算
XMFLOAT3 CalculateFloat3Sub(XMFLOAT3& a, XMFLOAT3& b)
{
    XMFLOAT3 result = { 0,0,0 };
    XMStoreFloat3(&result, XMVectorSubtract(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3型の2点間距離を計算する関数
float CalculateDistance(XMFLOAT3& point1, XMFLOAT3& point2)
{
    // ベクトルの長さを計算して距離を取得
    return XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&point1), XMLoadFloat3(&point2))));
}

// XMFLOAT3型の2点から向きベクトルを計算する関数
XMFLOAT3 CalculateDirection(XMFLOAT3& point1, XMFLOAT3& point2)
{
    // XMVECTORをXMFLOAT3に変換して返す
    XMFLOAT3 direction;
    XMStoreFloat3(&direction, XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&point1), XMLoadFloat3(&point2))));
    return direction;
}

// INIファイルからfloatを取得する関数
float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    // ファイル名
    TCHAR buffer[MAX_PATH];

    // 文字列を取得
    DWORD result = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);

    // 文字列が取得できたらfloatに変換して値を返す
    if (result != 0) return static_cast<float>(atof(buffer));
    else return static_cast<float>(atof(lpDefault));
}