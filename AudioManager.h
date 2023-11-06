#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class AudioManager : public GameObject
{
public:
    AudioManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Release() override;

    // オーディオ関連のメソッドを追加

private:
    // オーディオデータを管理するためのコンテナなどを宣言
};
