#include "Character.h"
#include <cmath>

// コンストラクタ
Character::Character(GameObject* parent, std::string name)
    : GameObject(parent, name)
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

// HPを増やす
void Character::IncreaseHp(float amount)
{
    commonStatus_.currentHp_ += amount;

    if (commonStatus_.currentHp_ > commonStatus_.maxHp_) 
    {
        // 最大値補正
        commonStatus_.currentHp_ = commonStatus_.maxHp_;
    }
}

// HPを減らす
void Character::DecreaseHp(float amount)
{
    commonStatus_.currentHp_ -= amount;

    if (commonStatus_.currentHp_ <= 0) 
    {
        // 最小値補正
        commonStatus_.currentHp_ = 0;

        // キャラクター死亡
        KillMe();
    }
}

// ノックバック処理
void Character::KnockBack(const XMFLOAT3& direction, float strength)
{
}
