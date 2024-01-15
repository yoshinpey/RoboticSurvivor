#pragma once
#include "Engine/Input.h"

// 入力状況を管理するクラス
class InputManager
{
public:
    // マウス入力
    static const int MOUSE_LEFT = 0;                        // マウス左ボタン
    static const int MOUSE_RIGHT = 1;                       // マウス右ボタン
    static const int SHOOT_KEY = MOUSE_LEFT;                // 射撃
    static const int WEAPON_ACTION_KEY = MOUSE_RIGHT;       // 武器アクション

    static bool IsShoot();                 // 射撃が行われているかどうか
    static bool IsWeaponAction();          // 武器アクションが行われているかどうか

    // キーボード入力
    static const int MOVE_FORWARD_KEY = DIK_W;      // 前進
    static const int MOVE_LEFT_KEY = DIK_A;         // 左移動
    static const int MOVE_BACKWARD_KEY = DIK_S;     // 後退
    static const int MOVE_RIGHT_KEY= DIK_D;         // 右移動
    static const int JUMP_KEY = DIK_SPACE;          // ジャンプ
    static const int RUN_KEY = DIK_LSHIFT;          // 走る
    static const int RELOAD_KEY = DIK_R;            // リロード
    static const int MENU_KEY = DIK_ESCAPE;         // メニュー
    static const int EVENT_ACTION_KEY = DIK_E;      // イベントアクション
    static const int ABILITY_KEY = DIK_Q;           // アビリティ

    static bool IsMoveForward();           // 前進中かどうか
    static bool IsMoveLeft();              // 左移動中かどうか
    static bool IsMoveBackward();          // 後退中かどうか
    static bool IsMoveRight();             // 右移動中かどうか

    static bool IsWalk();                  // 移動中かどうか
    static bool IsRun();                   // 走っているかどうか

    static bool IsJump();                  // ジャンプが行われているかどうか
    static bool IsReload();                // リロードが行われているかどうか
    static bool IsMenu();                  // メニューが開かれているかどうか
    static bool IsEventAction();           // イベントアクションが行われているかどうか
    static bool IsAbility();               // アビリティが使用されているかどうか
};
