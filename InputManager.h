#pragma once
#include "Engine/Input.h"

// ���͏󋵂��Ǘ�����
namespace InputManager
{
    bool IsShoot();                 // �ˌ����s���Ă��邩�ǂ���
    bool IsWeaponAction();          // ����A�N�V�������s���Ă��邩�ǂ���

    bool IsMoveForward();           // �O�i�����ǂ���
    bool IsMoveLeft();              // ���ړ������ǂ���
    bool IsMoveBackward();          // ��ޒ����ǂ���
    bool IsMoveRight();             // �E�ړ������ǂ���

    bool IsWalk();                  // �ړ������ǂ���
    bool IsRun();                   // �����Ă��邩�ǂ���

    bool IsJump();                  // �W�����v���s���Ă��邩�ǂ���
    bool IsReload();                // �����[�h���s���Ă��邩�ǂ���
    bool IsMenu();                  // ���j���[���J����Ă��邩�ǂ���
    bool IsEventAction();           // �C�x���g�A�N�V�������s���Ă��邩�ǂ���
    bool IsAbility();               // �A�r���e�B���g�p����Ă��邩�ǂ���
};
