#pragma once
#include "Engine/Input.h"

struct ButtonConfig;

// ���͏󋵂��Ǘ�����
namespace InputManager
{

    // �ˌ�
    bool IsShoot();

    // ����A�N�V����
    bool IsWeaponAction();

    // �O�i
    bool IsMoveForward();

    // ���ړ�
    bool IsMoveLeft();

    // ���
    bool IsMoveBackward();

    // �E�ړ�
    bool IsMoveRight();


    // �ړ���
    bool IsWalk();

    // �����Ă���
    bool IsRun();

    // �W�����v��
    bool IsJump();

    // �����[�h��
    bool IsReload();

    // ���j���[���J���Ă���
    bool IsMenu();

    // �C�x���g�A�N�V����
    bool IsEventAction();

    // �A�r���e�B���g�p
    bool IsAbility();
};