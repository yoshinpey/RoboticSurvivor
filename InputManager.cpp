
#include "InputManager.h"

namespace InputManager
{
	// �L�[�{�[�h����
	constexpr int  MOVE_FORWARD_KEY = DIK_W;      // �O�i
	constexpr int  MOVE_LEFT_KEY =  DIK_A;        // ���ړ�
	constexpr int  MOVE_BACKWARD_KEY = DIK_S;     // ���
	constexpr int  MOVE_RIGHT_KEY = DIK_D;        // �E�ړ�
	constexpr int  JUMP_KEY = DIK_SPACE;          // �W�����v
	constexpr int  RUN_KEY = DIK_LSHIFT;          // ����
	constexpr int  RELOAD_KEY = DIK_R;            // �����[�h
	constexpr int  MENU_KEY = DIK_ESCAPE;         // ���j���[
	constexpr int  EVENT_ACTION_KEY = DIK_E;      // �C�x���g�A�N�V����
	constexpr int  ABILITY_KEY = DIK_Q;           // �A�r���e�B

	// �}�E�X����
	constexpr int  MOUSE_LEFT = 0;                        // �}�E�X���{�^��
	constexpr int  MOUSE_RIGHT = 1;                       // �}�E�X�E�{�^��
	constexpr int  SHOOT_KEY = MOUSE_LEFT;                // �ˌ�
	constexpr int  WEAPON_ACTION_KEY = MOUSE_RIGHT;       // ����A�N�V����
}

bool InputManager::IsShoot() { return Input::IsMouseButtonDown(SHOOT_KEY); }
bool InputManager::IsWeaponAction() { return Input::IsMouseButtonUp(WEAPON_ACTION_KEY); }

bool InputManager::IsMoveForward() { return Input::IsKey(MOVE_FORWARD_KEY); }
bool InputManager::IsMoveLeft() { return Input::IsKey(MOVE_LEFT_KEY); }
bool InputManager::IsMoveBackward() { return Input::IsKey(MOVE_BACKWARD_KEY); }
bool InputManager::IsMoveRight() { return Input::IsKey(MOVE_RIGHT_KEY); }
bool InputManager::IsJump() { return Input::IsKeyDown(JUMP_KEY); }
bool InputManager::IsWalk() { return IsMoveForward() || IsMoveLeft() || IsMoveBackward() || IsMoveRight(); }
bool InputManager::IsRun() { return Input::IsKey(RUN_KEY); }
bool InputManager::IsReload() { return Input::IsKeyDown(RELOAD_KEY); }
bool InputManager::IsMenu() { return Input::IsKeyDown(MENU_KEY); }
bool InputManager::IsEventAction() { return Input::IsKeyDown(EVENT_ACTION_KEY); }
bool InputManager::IsAbility() { return Input::IsKeyDown(ABILITY_KEY); }