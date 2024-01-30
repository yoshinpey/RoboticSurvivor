#include "InputManager.h"

// �{�^���z�u�̐ݒ��ǂݍ��ފ֐�
void InputManager::LoadButtonConfig()
{
    std::ifstream configFile(CONFIG_FILE_PATH);
    if (configFile.is_open())
    {
        json configJson;
        configFile >> configJson;

        // �ݒ��ϐ��ɓǂݍ���
        MOVE_FORWARD_KEY = configJson["MOVE_FORWARD_KEY"];
        MOVE_LEFT_KEY = configJson["MOVE_LEFT_KEY"];
        MOVE_BACKWARD_KEY = configJson["MOVE_BACKWARD_KEY"];
        MOVE_RIGHT_KEY = configJson["MOVE_RIGHT_KEY"];
        JUMP_KEY = configJson["JUMP_KEY"];
        RUN_KEY = configJson["RUN_KEY"];
        RELOAD_KEY = configJson["RELOAD_KEY"];
        MENU_KEY = configJson["MENU_KEY"];
        EVENT_ACTION_KEY = configJson["EVENT_ACTION_KEY"];
        ABILITY_KEY = configJson["ABILITY_KEY"];
        MOUSE_LEFT = configJson["MOUSE_LEFT"];
        MOUSE_RIGHT = configJson["MOUSE_RIGHT"];
        SHOOT_KEY = configJson["SHOOT_KEY"];
        WEAPON_ACTION_KEY = configJson["WEAPON_ACTION_KEY"];

        configFile.close();
    }
}

// �������֐�
void InputManager::Initialize()
{
    // �ݒ�t�@�C������{�^���̐ݒ��ǂݍ���
    LoadButtonConfig();
}

// �X�V�֐�
void InputManager::Update()
{
    // �X�V����...
}

// �ˌ�
bool InputManager::IsShoot() const
{
    return Input::IsMouseButtonDown(SHOOT_KEY);
}

// ����A�N�V����
bool InputManager::IsWeaponAction() const
{
    return Input::IsMouseButtonUp(WEAPON_ACTION_KEY);
}

// �O�i
bool InputManager::IsMoveForward() const
{
    return Input::IsKey(MOVE_FORWARD_KEY);
}

// ���ړ�
bool InputManager::IsMoveLeft() const
{
    return Input::IsKey(MOVE_LEFT_KEY);
}

// ���
bool InputManager::IsMoveBackward() const
{
    return Input::IsKey(MOVE_BACKWARD_KEY);
}

// �E�ړ�
bool InputManager::IsMoveRight() const
{
    return Input::IsKey(MOVE_RIGHT_KEY);
}

// �ړ���
bool InputManager::IsWalk() const
{
    return IsMoveForward() || IsMoveLeft() || IsMoveBackward() || IsMoveRight();
}

// �����Ă���
bool InputManager::IsRun() const
{
    return Input::IsKey(RUN_KEY);
}

// �W�����v��
bool InputManager::IsJump() const
{
    return Input::IsKeyDown(JUMP_KEY);
}

// �����[�h��
bool InputManager::IsReload() const
{
    return Input::IsKey(RELOAD_KEY);
}

// ���j���[���J���Ă���
bool InputManager::IsMenu() const
{
    return Input::IsKey(MENU_KEY);
}

// �C�x���g�A�N�V����
bool InputManager::IsEventAction() const
{
    return Input::IsKey(EVENT_ACTION_KEY);
}

// �A�r���e�B���g�p
bool InputManager::IsAbility() const
{
    return Input::IsKey(ABILITY_KEY);
}
