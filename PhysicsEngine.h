#pragma once
#include <DirectXMath.h>

using namespace DirectX;

// �����^�����Ǘ�����N���X
class PhysicsEngine 
{
private:
    float gravity_;
    float acceleration_;
    float friction_;

public:
    PhysicsEngine();
    ~PhysicsEngine();

    // �d�͂�K�p
    void ApplyGravity(DirectX::XMFLOAT3& velocity, float delta);

    // �W�����v��K�p
    void ApplyJump(DirectX::XMFLOAT3& velocity, float jumpVelocity, float delta, bool& canJump, float& yPosition, float groundLevel);

    // ���C�͂�K�p
    void ApplyFriction(DirectX::XMFLOAT3& velocity, float delta);

    // �ړ��ʂ�K�p
    void ApplyMovement(DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& movement);

    float GetFriction() const;
    float GetJumpVelocity() const;
    void SetCanJump(bool value);
    bool CanJump() const;
};
