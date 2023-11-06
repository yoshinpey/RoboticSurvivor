#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class PlayerCamera : public GameObject
{
public:
    PlayerCamera(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override; // カメラの描画処理（必要な場合に記述）
    void Release() override;

    // カメラ制御に必要なメソッドを追加

private:
    // カメラのプロパティや状態を保持する変数を宣言
};
