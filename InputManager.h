// InputManager.h
#pragma once
#include "Engine/Input.h"

// ���͏󋵂��Ǘ�����N���X
class InputManager
{
public:
    // �}�E�X����
    static const int MOUSE_LEFT;           // �}�E�X���{�^��
    static const int MOUSE_RIGHT;          // �}�E�X�E�{�^��
    static const int SHOOT_KEY;            // �ˌ�
    static const int WEAPON_ACTION_KEY;    // ����A�N�V����

    static bool IsShoot();                 // �ˌ����s���Ă��邩�ǂ���
    static bool IsWeaponAction();          // ����A�N�V�������s���Ă��邩�ǂ���


    // �L�[�{�[�h����
    static const int MOVE_FORWARD_KEY;     // �O�i
    static const int MOVE_LEFT_KEY;        // ���ړ�
    static const int MOVE_BACKWARD_KEY;    // ���
    static const int MOVE_RIGHT_KEY;       // �E�ړ�
    static const int JUMP_KEY;             // �W�����v
    static const int RUN_KEY;              // ����
    static const int RELOAD_KEY;           // �����[�h
    static const int MENU_KEY;             // ���j���[
    static const int EVENT_ACTION_KEY;     // �C�x���g�A�N�V����
    static const int ABILITY_KEY;          // �A�r���e�B

    static bool IsMoveForward();           // �O�i�����ǂ���
    static bool IsMoveLeft();              // ���ړ������ǂ���
    static bool IsMoveBackward();          // ��ޒ����ǂ���
    static bool IsMoveRight();             // �E�ړ������ǂ���
    static bool IsJump();                  // �W�����v���s���Ă��邩�ǂ���
    static bool IsRun();                   // �����Ă��邩�ǂ���
    static bool IsReload();                // �����[�h���s���Ă��邩�ǂ���
    static bool IsMenu();                  // ���j���[���J����Ă��邩�ǂ���
    static bool IsEventAction();           // �C�x���g�A�N�V�������s���Ă��邩�ǂ���
    static bool IsAbility();               // �A�r���e�B���g�p����Ă��邩�ǂ���
};
