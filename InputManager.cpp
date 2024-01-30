#include "InputManager.h"

// ボタン配置の設定を読み込む関数
void InputManager::LoadButtonConfig()
{
    std::ifstream configFile(CONFIG_FILE_PATH);
    if (configFile.is_open())
    {
        json configJson;
        configFile >> configJson;

        // 設定を変数に読み込む
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

// 初期化関数
void InputManager::Initialize()
{
    // 設定ファイルからボタンの設定を読み込む
    LoadButtonConfig();
}

// 更新関数
void InputManager::Update()
{
    // 更新処理...
}

// 射撃
bool InputManager::IsShoot() const
{
    return Input::IsMouseButtonDown(SHOOT_KEY);
}

// 武器アクション
bool InputManager::IsWeaponAction() const
{
    return Input::IsMouseButtonUp(WEAPON_ACTION_KEY);
}

// 前進
bool InputManager::IsMoveForward() const
{
    return Input::IsKey(MOVE_FORWARD_KEY);
}

// 左移動
bool InputManager::IsMoveLeft() const
{
    return Input::IsKey(MOVE_LEFT_KEY);
}

// 後退
bool InputManager::IsMoveBackward() const
{
    return Input::IsKey(MOVE_BACKWARD_KEY);
}

// 右移動
bool InputManager::IsMoveRight() const
{
    return Input::IsKey(MOVE_RIGHT_KEY);
}

// 移動中
bool InputManager::IsWalk() const
{
    return IsMoveForward() || IsMoveLeft() || IsMoveBackward() || IsMoveRight();
}

// 走っている
bool InputManager::IsRun() const
{
    return Input::IsKey(RUN_KEY);
}

// ジャンプ中
bool InputManager::IsJump() const
{
    return Input::IsKeyDown(JUMP_KEY);
}

// リロード中
bool InputManager::IsReload() const
{
    return Input::IsKey(RELOAD_KEY);
}

// メニューを開いている
bool InputManager::IsMenu() const
{
    return Input::IsKey(MENU_KEY);
}

// イベントアクション
bool InputManager::IsEventAction() const
{
    return Input::IsKey(EVENT_ACTION_KEY);
}

// アビリティを使用
bool InputManager::IsAbility() const
{
    return Input::IsKey(ABILITY_KEY);
}
