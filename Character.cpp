#include "Character.h"
#include <cmath>

// コンストラクタ
Character::Character(GameObject* parent, std::string name)
    : GameObject(parent, name), knockDirection_(0.0f, 0.0f, 0.0f), isKnockBackActive_(false)
{
}

// デストラクタ
Character::~Character() = default;

// CommonParameterのコンストラクタ
Character::CommonParameter::CommonParameter()
    : jumpVelocity_(0.2f), walkSpeed_(0.1f), runSpeed_(0.2f), knockBackStrength_(1.0f)
{
}

// CommonStatusのコンストラクタ
Character::CommonStatus::CommonStatus()
    : maxHp_(100.0f), currentHp_(maxHp_)
{
}

// 更新メソッド
void Character::Update()
{
    if (isKnockBackActive_)
    {
        // ノックバック減衰
        knockDirection_.x -= knockDirection_.x * commonParameter_.knockBackStrength_;
        knockDirection_.z -= knockDirection_.z * commonParameter_.knockBackStrength_;

        // Y軸のノックバック減衰と重力適用
        knockDirection_.y -= knockDirection_.y * (commonParameter_.knockBackStrength_ * 3.0f);

        transform_.position_.x += knockDirection_.x;
        transform_.position_.y += knockDirection_.y;
        transform_.position_.z += knockDirection_.z;

        // 地面に到達したらジャンプ状態をリセット
        if (transform_.position_.y < 0)
        {
            transform_.position_.y = 0;
            knockDirection_.y = 0; // Y方向のノックバックをリセット
        }

        // ノックバックがほとんどなくなったらフラグをリセット
        if (fabs(knockDirection_.x) < 0.01f && fabs(knockDirection_.z) < 0.01f && fabs(knockDirection_.y) < 0.01f)
        {
            isKnockBackActive_ = false;
        }
    }
}

// HPを増やす
void Character::IncreaseHp(float amount)
{
    commonStatus_.currentHp_ += amount;
    if (commonStatus_.currentHp_ > commonStatus_.maxHp_) {
        commonStatus_.currentHp_ = commonStatus_.maxHp_;
    }
}

// HPを減らす
void Character::DecreaseHp(float amount)
{
    commonStatus_.currentHp_ -= amount;
    if (commonStatus_.currentHp_ <= 0) {
        commonStatus_.currentHp_ = 0;
        if (IsCharacterDead()) KillMe();
    }
}

// 死亡判定
bool Character::IsCharacterDead()
{
    return commonStatus_.currentHp_ <= 0.0f;
}

// ノックバック処理
void Character::KnockBack(const XMFLOAT3& direction, float strength)
{
    // ノックバック方向を設定
    knockDirection_ = direction;
    knockDirection_.x *= strength;
    knockDirection_.y = 1.0f; // 上方向へのノックバックは固定値
    knockDirection_.z *= strength;

    isKnockBackActive_ = true;
}
