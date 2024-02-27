#include "Enemy_Ground.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr), lastAngle_(0)
{
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Ground", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Ground", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Ground", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Ground", "attackDistance", 0, "Settings/EnemySettings.ini");
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

}

void Enemy_Ground::Update()
{
    // プレイヤーへの方向ベクトル(正規化済)
    XMFLOAT3 direction = CheckPlayerDirection();

    // プレイヤーが視界内にいるかどうか
    if (IsPlayerInFieldOfView())
    {
        // プレイヤーまでの距離
        float dist = CheckPlayerDistance();
        //OutputDebugString(std::to_string(dist).c_str());
        //OutputDebugString("\n");
    }

    // デバッグ用、視野角に入ってるか確認するための変形
    transform_.scale_.y = IsPlayerInFieldOfView() ? 0.2f : 1.0f;
}

bool Enemy_Ground::IsPlayerInFieldOfView()
{
    const float fieldOfView = XMConvertToRadians(20.0f); // 視界角度をラジアンに変換
    XMFLOAT3 enemyForward = CheckPlayerDirection();

    // プレイヤーへの方向ベクトル(正規化済)
    XMFLOAT3 toPlayer = CheckPlayerDirection();

    // 視界の方向ベクトルをプレイヤーへの方向ベクトルに向けて徐々に回転させる
    float angle = acos(XMVectorGetX(XMVector3Dot(XMLoadFloat3(&enemyForward), XMLoadFloat3(&toPlayer)))); // 敵とプレイヤーの方向ベクトルの内積から角度を求める
    float rotateSpeed = XMConvertToRadians(1.0f); // 視界の回転速度（1度ずつ回転）

    if (angle > rotateSpeed)
    {
        // 視界の方向ベクトルを徐々にプレイヤーへの方向ベクトルに向ける
        XMFLOAT3 newEnemyForward;
        XMStoreFloat3(&newEnemyForward, XMVector3Normalize(XMLoadFloat3(&enemyForward) + XMLoadFloat3(&toPlayer) * rotateSpeed));
        enemyForward = newEnemyForward;
    }
    else
    {
        // 視界の方向ベクトルがほぼプレイヤーへの方向ベクトルと一致する場合、完全に一致させる
        enemyForward = toPlayer;
    }

    // 視界の方向ベクトルとプレイヤーへの方向ベクトルの角度が視界角度の半分以下であればプレイヤーが視界内にいると判定
    angle = acos(XMVectorGetX(XMVector3Dot(XMLoadFloat3(&enemyForward), XMLoadFloat3(&toPlayer)))); // 更新した視界の方向ベクトルとプレイヤーへの方向ベクトルの内積から角度を再計算

    // 視界の方向を更新
    transform_.rotate_.y = atan2(enemyForward.x, enemyForward.z);

    return angle <= fieldOfView / 2;
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

