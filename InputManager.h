#pragma once
#include "Engine/Input.h"

// 入力状況を管理する
namespace InputManager
{
    bool IsShoot();                 // 射撃が行われているかどうか
    bool IsWeaponAction();          // 武器アクションが行われているかどうか

    bool IsMoveForward();           // 前進中かどうか
    bool IsMoveLeft();              // 左移動中かどうか
    bool IsMoveBackward();          // 後退中かどうか
    bool IsMoveRight();             // 右移動中かどうか

    bool IsWalk();                  // 移動中かどうか
    bool IsRun();                   // 走っているかどうか

    bool IsJump();                  // ジャンプが行われているかどうか
    bool IsReload();                // リロードが行われているかどうか
    bool IsMenu();                  // メニューが開かれているかどうか
    bool IsEventAction();           // イベントアクションが行われているかどうか
    bool IsAbility();               // アビリティが使用されているかどうか
};
