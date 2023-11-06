#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class UIManager : public GameObject
{
public:
    UIManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Release() override;

    // UI関連のメソッドを追加

private:
    // UI要素を管理するためのコンテナなどを宣言
};
