#include "Enemy_Ground.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr)
{
}

Enemy_Ground::~Enemy_Ground()
{
}

void Enemy_Ground::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load("Character/Enemy_02.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // 当たり判定付与
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 2.0f);
    AddCollider(pCollision_);

#if 0
    /*
    構造体丸ごと取得できるはずなのに上手くいかない
    BOOL GetPrivateProfileStruct(
      [in]  LPCTSTR lpszSection,        // 初期化ファイル内のセクションの名前。
      [in]  LPCTSTR lpszKey,            // データを取得するキーの名前。
      [out] LPVOID  lpStruct,           // ファイル、セクション、およびキー名に関連付けられたデータを受け取るバッファーへのポインター。
      [in]  UINT    uSizeStruct,        // lpStruct パラメーターが指すバッファーのサイズ (バイト単位)。
      [in]  LPCTSTR szFile              // 初期化ファイルの名前。
    );

    戻り値
    成功：0以外
    失敗：0
    */

    // INIファイルからデータを構造体へ流し込む
    GetPrivateProfileStruct("Enemy_Ground_status", "", &status_, sizeof(EnemyStatus), "Settings/EnemySettingsStruct.ini");
    GetPrivateProfileStruct("Enemy_Ground_algorithm", "", &algorithm_, sizeof(EnemyAlgorithm), "Settings/EnemySettingsStruct.ini");
    
#else
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_ = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_ = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_ = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
#endif
}

void Enemy_Ground::Update()
{
#if 0
    OutputDebugStringA(("walkSpeed: " + std::to_string(status_.walkSpeed_) + "\n").c_str());
    transform_.position_.x += status_.walkSpeed_;

    OutputDebugStringA(("Size of EnemyStatus: " + std::to_string(sizeof(status_)) + "\n").c_str());
#endif
}

void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{
    /*
    // 銃弾に当たったとき
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Ground::Attack()
{
}
