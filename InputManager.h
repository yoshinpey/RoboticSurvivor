#pragma once
#include "Engine/Input.h"

// ���͏󋵂��Ǘ�����N���X
class InputManager
{
public:
    // �}�E�X����
    static const int MOUSE_LEFT = 0;                        // �}�E�X���{�^��
    static const int MOUSE_RIGHT = 1;                       // �}�E�X�E�{�^��
    static const int SHOOT_KEY = MOUSE_LEFT;                // �ˌ�
    static const int WEAPON_ACTION_KEY = MOUSE_RIGHT;       // ����A�N�V����

    static bool IsShoot();                 // �ˌ����s���Ă��邩�ǂ���
    static bool IsWeaponAction();          // ����A�N�V�������s���Ă��邩�ǂ���

    // �L�[�{�[�h����
    static const int MOVE_FORWARD_KEY = DIK_W;      // �O�i
    static const int MOVE_LEFT_KEY = DIK_A;         // ���ړ�
    static const int MOVE_BACKWARD_KEY = DIK_S;     // ���
    static const int MOVE_RIGHT_KEY= DIK_D;         // �E�ړ�
    static const int JUMP_KEY = DIK_SPACE;          // �W�����v
    static const int RUN_KEY = DIK_LSHIFT;          // ����
    static const int RELOAD_KEY = DIK_R;            // �����[�h
    static const int MENU_KEY = DIK_ESCAPE;         // ���j���[
    static const int EVENT_ACTION_KEY = DIK_E;      // �C�x���g�A�N�V����
    static const int ABILITY_KEY = DIK_Q;           // �A�r���e�B

    static bool IsMoveForward();           // �O�i�����ǂ���
    static bool IsMoveLeft();              // ���ړ������ǂ���
    static bool IsMoveBackward();          // ��ޒ����ǂ���
    static bool IsMoveRight();             // �E�ړ������ǂ���

    static bool IsWalk();                  // �ړ������ǂ���
    static bool IsRun();                   // �����Ă��邩�ǂ���

    static bool IsJump();                  // �W�����v���s���Ă��邩�ǂ���
    static bool IsReload();                // �����[�h���s���Ă��邩�ǂ���
    static bool IsMenu();                  // ���j���[���J����Ă��邩�ǂ���
    static bool IsEventAction();           // �C�x���g�A�N�V�������s���Ă��邩�ǂ���
    static bool IsAbility();               // �A�r���e�B���g�p����Ă��邩�ǂ���
};
