#include "Animation.h"

Animation::Animation(GameObject* parent)
    : GameObject(parent, "Animation")
{
}

void Animation::Initialize()
{
    // アニメーションの初期化処理をここに記述
}

void Animation::Update()
{
    // アニメーションの更新
}

void Animation::Draw()
{
    // アニメーションの描画
}

void Animation::Release()
{
    // アニメーションのリソース解放処理
}
