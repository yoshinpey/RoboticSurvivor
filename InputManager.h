#pragma once
#include "Engine/Input.h"

struct ButtonConfig;

// 入力状況を管理する
namespace InputManager
{

    // 射撃
    bool IsShoot();

    // 武器アクション
    bool IsWeaponAction();

    // 前進
    bool IsMoveForward();

    // 左移動
    bool IsMoveLeft();

    // 後退
    bool IsMoveBackward();

    // 右移動
    bool IsMoveRight();


    // 移動中
    bool IsWalk();

    // 走っている
    bool IsRun();

    // ジャンプ中
    bool IsJump();

    // リロード中
    bool IsReload();

    // メニューを開いている
    bool IsMenu();

    // イベントアクション
    bool IsEventAction();

    // アビリティを使用
    bool IsAbility();
};