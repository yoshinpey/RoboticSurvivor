// InputManager.h
#pragma once
#include "Engine/Input.h"

// 入力状況を管理するクラス
class InputManager
{
public:
    // マウス入力
    static const int MOUSE_LEFT;           // マウス左ボタン
    static const int MOUSE_RIGHT;          // マウス右ボタン
    static const int SHOOT_KEY;            // 射撃
    static const int WEAPON_ACTION_KEY;    // 武器アクション

    static bool IsShoot();                 // 射撃が行われているかどうか
    static bool IsWeaponAction();          // 武器アクションが行われているかどうか


    // キーボード入力
    static const int MOVE_FORWARD_KEY;     // 前進
    static const int MOVE_LEFT_KEY;        // 左移動
    static const int MOVE_BACKWARD_KEY;    // 後退
    static const int MOVE_RIGHT_KEY;       // 右移動
    static const int JUMP_KEY;             // ジャンプ
    static const int RUN_KEY;              // 走る
    static const int RELOAD_KEY;           // リロード
    static const int MENU_KEY;             // メニュー
    static const int EVENT_ACTION_KEY;     // イベントアクション
    static const int ABILITY_KEY;          // アビリティ

    static bool IsMoveForward();           // 前進中かどうか
    static bool IsMoveLeft();              // 左移動中かどうか
    static bool IsMoveBackward();          // 後退中かどうか
    static bool IsMoveRight();             // 右移動中かどうか
    static bool IsJump();                  // ジャンプが行われているかどうか
    static bool IsRun();                   // 走っているかどうか
    static bool IsReload();                // リロードが行われているかどうか
    static bool IsMenu();                  // メニューが開かれているかどうか
    static bool IsEventAction();           // イベントアクションが行われているかどうか
    static bool IsAbility();               // アビリティが使用されているかどうか
};
