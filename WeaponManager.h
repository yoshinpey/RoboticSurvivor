#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class WeaponManager : public GameObject
{
public:
    WeaponManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // 武器関連のメソッドを追加

private:
    // 武器データを管理するためのコンテナなどを宣言
};
