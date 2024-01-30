#pragma once
#include "Engine/Input.h"
#include "json.hpp"
#include <fstream>
#include <string>

class InputManager
{
private:
    // �}�E�X����
    int MOUSE_LEFT;        // �}�E�X���{�^��
    int MOUSE_RIGHT;       // �}�E�X�E�{�^��
    int SHOOT_KEY;         // �ˌ�
    int WEAPON_ACTION_KEY; // ����A�N�V����

    // �L�[�{�[�h����
    int MOVE_FORWARD_KEY;    // �O�i
    int MOVE_LEFT_KEY;       // ���ړ�
    int MOVE_BACKWARD_KEY;   // ���
    int MOVE_RIGHT_KEY;      // �E�ړ�
    int JUMP_KEY;            // �W�����v
    int RUN_KEY;             // ����
    int RELOAD_KEY;          // �����[�h
    int MENU_KEY;            // ���j���[
    int EVENT_ACTION_KEY;    // �C�x���g�A�N�V����
    int ABILITY_KEY;         // �A�r���e�B

    // �ݒ�t�@�C���̃p�X
    const char* CONFIG_FILE_PATH = "input_config.json";

    // �{�^���z�u�̐ݒ��ǂݍ��ފ֐�
    void LoadButtonConfig();

public:
    using json = nlohmann::json;
    // �������֐�
    void Initialize();

    // �X�V�֐�
    void Update();

    // �ˌ�
    bool IsShoot() const;

    // ����A�N�V����
    bool IsWeaponAction() const;

    // �O�i
    bool IsMoveForward() const;

    // ���ړ�
    bool IsMoveLeft() const;

    // ���
    bool IsMoveBackward() const;

    // �E�ړ�
    bool IsMoveRight() const;

    // �ړ���
    bool IsWalk() const;

    // �����Ă���
    bool IsRun() const;

    // �W�����v��
    bool IsJump() const;

    // �����[�h��
    bool IsReload() const;

    // ���j���[���J���Ă���
    bool IsMenu() const;

    // �C�x���g�A�N�V����
    bool IsEventAction() const;

    // �A�r���e�B���g�p
    bool IsAbility() const;
};