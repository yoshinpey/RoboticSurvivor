#include "InputManager.h"

bool InputManager::IsShoot() { return Input::IsMouseButtonDown(SHOOT_KEY); }
bool InputManager::IsWeaponAction() { return Input::IsMouseButtonUp(WEAPON_ACTION_KEY); }

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
