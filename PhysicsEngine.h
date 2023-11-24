#pragma once
#include <DirectXMath.h>

using namespace DirectX;

// 物理運動を管理するクラス
class PhysicsEngine 
{
private:
    float gravity_;
    float acceleration_;
    float friction_;

public:
    PhysicsEngine();
    ~PhysicsEngine();

    // 重力を適用
    void ApplyGravity(DirectX::XMFLOAT3& velocity, float delta);

    // ジャンプを適用
    void ApplyJump(DirectX::XMFLOAT3& velocity, float jumpVelocity, float delta, bool& canJump, float& yPosition, float groundLevel);

    // 摩擦力を適用
    void ApplyFriction(DirectX::XMFLOAT3& velocity, float delta);

    // 移動量を適用
    void ApplyMovement(DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& movement);

    float GetFriction() const;
    float GetJumpVelocity() const;
    void SetCanJump(bool value);
    bool CanJump() const;
};
