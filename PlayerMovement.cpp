//// PlayerMovement.cpp
//#include "PlayerMovement.h"
//
//PlayerMovement::PlayerMovement(Player* player)
//    : player_(player), isMoving_(false), movement_(XMFLOAT3(0.0f, 0.0f, 0.0f)), velocity_(XMFLOAT3(0.0f, 0.0f, 0.0f)),
//    walkSpeed_(WALK_SPEED), runSpeed_(RUN_SPEED), acceleration_(0.01f), friction_(0.8f) {}
//
//void PlayerMovement::Move() 
//{
//    XMFLOAT3 fMove = CalculateMoveInput();
//    isMoving_ = InputManager::IsMoveForward() || InputManager::IsMoveLeft() || InputManager::IsMoveBackward() || InputManager::IsMoveRight();
//
//    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&movement_)));
//    float maxMoveSpeed = 0.0f;
//
//    if (isMoving_)
//    {
//        if (InputManager::IsRun()) 
//        {
//            maxMoveSpeed = runSpeed_;
//        }
//        else 
//        {
//            maxMoveSpeed = walkSpeed_;
//        }
//
//        ApplyAcceleration(currentSpeed, maxMoveSpeed);
//
//        movement_.x += fMove.x * velocity_.x;
//        movement_.z += fMove.z * velocity_.z;
//
//        player_->transform_.position_.x += movement_.x;
//        player_->transform_.position_.z += movement_.z;
//    }
//    else {
//        ApplyDeceleration();
//
//        player_->transform_.position_.x += movement_.x;
//        player_->transform_.position_.z += movement_.z;
//    }
//}
//
//void PlayerMovement::Jump() {
//    if (InputManager::IsJump() && player_->canJump_) {
//        velocity_.y = player_->jumpVelocity_;
//        player_->canJump_ = false;
//    }
//
//    if (!player_->canJump_) {
//        player_->transform_.position_.y += velocity_.y * player_->jumpDelta_;
//        velocity_.y += player_->gravity_ * player_->jumpDelta_;
//
//        if (player_->transform_.position_.y <= 0) {
//            player_->transform_.position_.y = 0;
//            velocity_.y = 0.0f;
//            player_->canJump_ = true;
//        }
//    }
//}
//
//void PlayerMovement::ApplyAcceleration(float& currentSpeed, float maxMoveSpeed) {
//    if (currentSpeed > maxMoveSpeed) {
//        XMVECTOR vMove = XMLoadFloat3(&movement_);
//        vMove = XMVector3Normalize(vMove);
//        vMove *= maxMoveSpeed;
//        XMStoreFloat3(&movement_, vMove);
//    }
//
//    if (currentSpeed < maxMoveSpeed) {
//        velocity_.x += acceleration_;
//        velocity_.z += acceleration_;
//    }
//    else {
//        velocity_.x = maxMoveSpeed;
//        velocity_.z = maxMoveSpeed;
//    }
//}
//
//void PlayerMovement::ApplyDeceleration() {
//    movement_.x *= friction_;
//    movement_.z *= friction_;
//    velocity_.x = 0;
//    velocity_.z = 0;
//}
//
//XMFLOAT3 PlayerMovement::CalculateMoveInput() {
//    XMFLOAT3 fMove = XMFLOAT3(0.0f, 0.0f, 0.0f);
//
//    Aim* pAim = (Aim*)FindObject("Aim");
//    XMFLOAT3 aimDirection = pAim->GetAimDirection();
//
//    if (InputManager::IsMoveForward()) {
//        fMove.x += aimDirection.x;
//        fMove.z += aimDirection.z;
//    }
//    if (InputManager::IsMoveLeft()) {
//        fMove.x -= aimDirection.z;
//        fMove.z += aimDirection.x;
//    }
//    if (InputManager::IsMoveBackward()) {
//        fMove.x -= aimDirection.x;
//        fMove.z -= aimDirection.z;
//    }
//    if (InputManager::IsMoveRight()) {
//        fMove.x += aimDirection.z;
//        fMove.z -= aimDirection.x;
//    }
//
//    XMVECTOR vMove = XMLoadFloat3(&fMove);
//    vMove = XMVector3Normalize(vMove);
//    XMStoreFloat3(&fMove, vMove);
//
//    return fMove;
//}