#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// 方向ベクトル
static constexpr XMFLOAT3 UP_VECTOR = { 0.0f, 1.0f, 0.0f };         //上
static constexpr XMFLOAT3 DOWN_VECTOR = { 0.0f, -1.0f, 0.0f };      //下
static constexpr XMFLOAT3 RIGHT_VECTOR = { 1.0f, 0.0f, 0.0f };      //右
static constexpr XMFLOAT3 LEFT_VECTOR = { -1.0f, 0.0f, 0.0f };      //左
static constexpr XMFLOAT3 FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };    //前
static constexpr XMFLOAT3 BACKWARD_VECTOR = { 0.0f, 0.0f, -1.0f };  //後

// 1度ベクトルに変換した方がSIMD演算(同時演算)を活用できるため効率的らしい
// 以下、各種計算関数

// XMFLOAT3を正規化する関数
// 引数:正規化したいFLOAT3型
// 戻り値：正規化したFLOAT3型
static XMFLOAT3 NormalizeFloat3(XMFLOAT3& vec)
{
    XMVECTOR v = XMVector3Normalize(XMLoadFloat3(&vec));
    XMStoreFloat3(&vec, v);
    return vec;
}

// XMFLOAT3の加算
// 戻り値 = a + b
static XMFLOAT3 CalculateFloat3Add(XMFLOAT3& a, XMFLOAT3& b)
{
    XMFLOAT3 result = {0,0,0};
    XMStoreFloat3(&result, XMVectorAdd(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3の減算
// 戻り値 = a - b
static XMFLOAT3 CalculateFloat3Sub(XMFLOAT3& a, XMFLOAT3& b)
{
    XMFLOAT3 result = { 0,0,0 };
    XMStoreFloat3(&result, XMVectorSubtract(XMLoadFloat3(&a), XMLoadFloat3(&b)));
    return result;
}

// XMFLOAT3型の2点間距離を計算する関数 
// 戻り値 = |point2 - point1|
static float CalculateDistance(XMFLOAT3 point1, XMFLOAT3 point2)
{
    // ベクトルの長さを計算して距離を取得
    return XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&point2), XMLoadFloat3(&point1))));
}

// XMFLOAT3型の2点から向きベクトルを計算する関数
// 戻り値 = ポイント1からポイント2へ向かう方向ベクトル
static XMFLOAT3 CalculateDirection(XMFLOAT3 point1, XMFLOAT3 point2)
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
