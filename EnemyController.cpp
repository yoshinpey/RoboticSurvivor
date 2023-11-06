#include "EnemyController.h"

EnemyController::EnemyController(GameObject* parent)
    : GameObject(parent, "EnemyController")
{
}

void EnemyController::Initialize()
{
    // EnemyControllerの初期化処理をここに記述
}

void EnemyController::Update()
{
    // 敵の行動を制御
}

void EnemyController::Draw()
{
    // 敵の描画
}

void EnemyController::Release()
{
    // 敵コントローラーのリソース解放処理
}
