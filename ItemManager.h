#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class ItemManager : public GameObject
{
public:
    ItemManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // アイテム関連のメソッドを追加

private:
    // アイテムデータを管理するためのコンテナなどを宣言
};
