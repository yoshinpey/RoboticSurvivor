// InputManager.cpp
#include "InputManager.h"

const int InputManager::MOUSE_LEFT = 0;
const int InputManager::MOUSE_RIGHT = 1;
const int InputManager::SHOOT_KEY = InputManager::MOUSE_LEFT;
const int InputManager::WEAPON_ACTION_KEY = InputManager::MOUSE_RIGHT;

bool InputManager::IsShoot() { return Input::IsMouseButtonDown(SHOOT_KEY); }
bool InputManager::IsWeaponAction() { return Input::IsMouseButtonUp(WEAPON_ACTION_KEY); }

const int InputManager::MOVE_FORWARD_KEY = DIK_W;
const int InputManager::MOVE_LEFT_KEY = DIK_A;
const int InputManager::MOVE_BACKWARD_KEY = DIK_S;
const int InputManager::MOVE_RIGHT_KEY = DIK_D;
const int InputManager::JUMP_KEY = DIK_SPACE;
const int InputManager::RUN_KEY = DIK_LSHIFT;
const int InputManager::RELOAD_KEY = DIK_R;
const int InputManager::MENU_KEY = DIK_ESCAPE;
const int InputManager::EVENT_ACTION_KEY = DIK_E;
const int InputManager::ABILITY_KEY = DIK_Q;

bool InputManager::IsMoveForward() { return Input::IsKey(MOVE_FORWARD_KEY); }
bool InputManager::IsMoveLeft() { return Input::IsKey(MOVE_LEFT_KEY); }
bool InputManager::IsMoveBackward() { return Input::IsKey(MOVE_BACKWARD_KEY); }
bool InputManager::IsMoveRight() { return Input::IsKey(MOVE_RIGHT_KEY); }
bool InputManager::IsJump() { return Input::IsKeyDown(JUMP_KEY); }
bool InputManager::IsRun() { return Input::IsKey(RUN_KEY); }
bool InputManager::IsReload() { return Input::IsKeyDown(RELOAD_KEY); }
bool InputManager::IsMenu() { return Input::IsKeyDown(MENU_KEY); }
bool InputManager::IsEventAction() { return Input::IsKeyDown(EVENT_ACTION_KEY); }
bool InputManager::IsAbility() { return Input::IsKeyDown(ABILITY_KEY); }
