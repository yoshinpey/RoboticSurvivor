#include "AudioManager.h"
#include "PlayerCharacter.h" // 必要なヘッダファイルをインクルード

AudioManager::AudioManager(GameObject* parent)
    : GameObject(parent, "AudioManager")
{
}

void AudioManager::Initialize()
{
    // オーディオの初期化処理を記述
}

void AudioManager::Update()
{
    // オーディオの更新処理を記述
}

void AudioManager::Release()
{
    // オーディオのリソース解放処理を記述
}

// オーディオ関連のメソッドを追加
