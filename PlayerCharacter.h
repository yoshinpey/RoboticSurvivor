#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class PlayerCharacter : public GameObject
{
public:
    PlayerCharacter(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override; // ドロー関数を追加
    void Release() override;

    // プレイヤーキャラクターの行動を制御するメソッドを追加

private:
    // プレイヤーキャラクターのステータスやアクションに必要な変数を宣言
};
