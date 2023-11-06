#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(GameObject* parent)
    : GameObject(parent, "PlayerCamera")
{
}

void PlayerCamera::Initialize()
{
    // カメラの初期化処理を記述
}

void PlayerCamera::Update()
{
    // カメラの更新処理を記述
}

void PlayerCamera::Draw()
{
    // カメラの描画処理を記述
    // 通常、カメラ自体は描画されないが、カメラのビュー行列を設定することは重要
}

void PlayerCamera::Release()
{
    // カメラの解放処理を記述
}
