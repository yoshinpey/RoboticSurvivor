#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// 方向ベクトル
static constexpr XMFLOAT3 UP_VECTOR = { 0.0f, 1.0f, 0.0f };
static constexpr XMFLOAT3 DOWN_VECTOR = { 0.0f, -1.0f, 0.0f };
static constexpr XMFLOAT3 RIGHT_VECTOR = { 1.0f, 0.0f, 0.0f };
static constexpr XMFLOAT3 LEFT_VECTOR = { -1.0f, 0.0f, 0.0f };
static constexpr XMFLOAT3 FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };
static constexpr XMFLOAT3 BACKWARD_VECTOR = { 0.0f, 0.0f, -1.0f };

// 正規化
static void NormalizeFloat3(XMFLOAT3& vec)
{
    XMVECTOR v = XMLoadFloat3(&vec);
    v = XMVector3Normalize(v);
    XMStoreFloat3(&vec, v);
}

// XMFLOAT3型の2点間距離を計算する関数 
// 戻り値 = |point2 - point1|
static float CalculateDistance(const XMFLOAT3& point1, const XMFLOAT3& point2)
{
    // 1度ベクトルに変換した方がSIMD演算(同時演算)を活用できるため効率的らしい
    // ベクトルの長さを計算して距離を取得
    return XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&point2), XMLoadFloat3(&point1))));
}

// XMFLOAT3型の2点から向きベクトルを計算する関数
// 戻り値 = ポイント1からポイント2へ向かう方向ベクトル
static XMFLOAT3 CalculateDirection(const XMFLOAT3& point1, const XMFLOAT3& point2)
{
    // XMVECTORをXMFLOAT3に変換して返す
    XMFLOAT3 direction;
    XMStoreFloat3(&direction, XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&point2), XMLoadFloat3(&point1))));
    return direction;
}

// INIファイルからfloatを取得する関数
static float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    // ファイル名
    TCHAR buffer[MAX_PATH];

    // 文字列を取得
    DWORD result = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer), lpFileName);
    
    // 文字列が取得できたらfloatに変換して値を返す
    if (result != 0) return static_cast<float>(atof(buffer));
    else return static_cast<float>(atof(lpDefault));
}
