// InputManager.h
#pragma once
#include "Engine/Input.h"


class InputManager
{
public:
    // mouse
    static const int MOUSE_LEFT = 0;
    static const int MOUSE_RIGHT = 1;
    static const int SHOOT_KEY = MOUSE_LEFT;
    static const int WEAPON_ACTION_KEY = MOUSE_RIGHT;

    static bool IsShoot() { return Input::IsMouseButtonDown(SHOOT_KEY); }
    static bool IsWeaponAction() { return Input::IsMouseButtonUp(WEAPON_ACTION_KEY); }

    // key
    static const int MOVE_FORWARD_KEY = DIK_W;
    static const int MOVE_LEFT_KEY = DIK_A;
    static const int MOVE_BACKWARD_KEY = DIK_S;
    static const int MOVE_RIGHT_KEY = DIK_D;
    static const int JUMP_KEY = DIK_SPACE;
    static const int RUN_KEY = DIK_LSHIFT;
    static const int RELOAD_KEY = DIK_R;
    static const int MENU_KEY = DIK_ESCAPE;
    static const int EVENT_ACTION_KEY = DIK_E;
    static const int ABILITY_KEY = DIK_Q;

    static bool IsMoveForward() { return Input::IsKey(MOVE_FORWARD_KEY); }
    static bool IsMoveLeft() { return Input::IsKey(MOVE_LEFT_KEY); }
    static bool IsMoveBackward() { return Input::IsKey(MOVE_BACKWARD_KEY); }
    static bool IsMoveRight() { return Input::IsKey(MOVE_RIGHT_KEY); }
    static bool IsJump() { return Input::IsKeyDown(JUMP_KEY); }
    static bool IsRun() { return Input::IsKey(RUN_KEY); }
    static bool IsReload() { return Input::IsKeyDown(RELOAD_KEY); }
    static bool IsMenu() { return Input::IsKeyDown(MENU_KEY); }
    static bool IsEventAction() { return Input::IsKeyDown(EVENT_ACTION_KEY); }
    static bool IsAbility() { return Input::IsKeyDown(ABILITY_KEY); }
};
