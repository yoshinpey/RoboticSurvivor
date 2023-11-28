//// PlayerMovement.h
//#pragma once
//#include "InputManager.h"
//
//#include "Aim.h"
//#include "Player.h"
//
//class PlayerMovement {
//public:
//    PlayerMovement(Player* player);
//
//    void Move();
//    void Jump();
//
//private:
//    Player* player_;
//
//    bool isMoving_;
//    XMFLOAT3 movement_;
//    XMFLOAT3 velocity_;
//
//    float walkSpeed_;
//    float runSpeed_;
//    float acceleration_;
//    float friction_;
//
//    void ApplyAcceleration(float& currentSpeed, float maxMoveSpeed);
//    void ApplyDeceleration();
//    XMFLOAT3 CalculateMoveInput();
//};