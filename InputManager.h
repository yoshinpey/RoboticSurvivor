#pragma once
#include "Engine/Input.h"
#include "json.hpp"
#include <fstream>
#include <string>

class InputManager
{
private:
    // マウス入力
    int MOUSE_LEFT;        // マウス左ボタン
    int MOUSE_RIGHT;       // マウス右ボタン
    int SHOOT_KEY;         // 射撃
    int WEAPON_ACTION_KEY; // 武器アクション

    // キーボード入力
    int MOVE_FORWARD_KEY;    // 前進
    int MOVE_LEFT_KEY;       // 左移動
    int MOVE_BACKWARD_KEY;   // 後退
    int MOVE_RIGHT_KEY;      // 右移動
    int JUMP_KEY;            // ジャンプ
    int RUN_KEY;             // 走る
    int RELOAD_KEY;          // リロード
    int MENU_KEY;            // メニュー
    int EVENT_ACTION_KEY;    // イベントアクション
    int ABILITY_KEY;         // アビリティ

    // 設定ファイルのパス
    const char* CONFIG_FILE_PATH = "input_config.json";

    // ボタン配置の設定を読み込む関数
    void LoadButtonConfig();

public:
    using json = nlohmann::json;
    // 初期化関数
    void Initialize();

    // 更新関数
    void Update();

    // 射撃
    bool IsShoot() const;

    // 武器アクション
    bool IsWeaponAction() const;

    // 前進
    bool IsMoveForward() const;

    // 左移動
    bool IsMoveLeft() const;

    // 後退
    bool IsMoveBackward() const;

    // 右移動
    bool IsMoveRight() const;

    // 移動中
    bool IsWalk() const;

    // 走っている
    bool IsRun() const;

    // ジャンプ中
    bool IsJump() const;

    // リロード中
    bool IsReload() const;

    // メニューを開いている
    bool IsMenu() const;

    // イベントアクション
    bool IsEventAction() const;

    // アビリティを使用
    bool IsAbility() const;
};