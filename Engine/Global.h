#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// 1度ベクトルに変換した方がSIMD演算(同時演算)を活用できるため効率的らしい
// 以下、各種計算関数

// XMFLOAT3を正規化する関数
// 引数:正規化したいFLOAT3型
// 戻り値：正規化したFLOAT3型
XMFLOAT3 NormalizeFloat3(XMFLOAT3& vec);

// XMFLOAT3の加算
// 戻り値 = a + b
XMFLOAT3 CalculateFloat3Add(XMFLOAT3& a, XMFLOAT3& b);

// XMFLOAT3の減算
// 戻り値 = a - b
XMFLOAT3 CalculateFloat3Sub(XMFLOAT3& a, XMFLOAT3& b);

// XMFLOAT3型の2点間距離を計算する関数 
// 戻り値 = |point1 - point2|
float CalculateDistance(XMFLOAT3& point1, XMFLOAT3& point2);

// XMFLOAT3型の2点から向きベクトルを計算する関数
// 戻り値 = ポイント2からポイント1へ向かう方向ベクトル
XMFLOAT3 CalculateDirection(XMFLOAT3& point1, XMFLOAT3& point2);

// INIファイルからfloatを取得する関数
float GetPrivateProfileFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName);
