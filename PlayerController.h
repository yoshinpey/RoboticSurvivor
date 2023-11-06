#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class PlayerController : public GameObject
{
public:
    PlayerController(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Release() override;

    // プレイヤーの行動を制御するメソッドを追加

private:
    // プレイヤーの行動に必要な変数やオブジェクトを宣言
};
