#include "EventManager.h"
#include "TitleScene.h"

EventManager::EventManager(GameObject* parent)
    : GameObject(parent, "EventManager")
{
}

void EventManager::Initialize()
{
    // イベントの初期化処理を記述
}

void EventManager::Update()
{
    // イベントの更新処理を記述
    UpdateEvents();
}

void EventManager::Draw()
{
    // イベントの描画処理を記述
}

void EventManager::Release()
{
    // イベントのリソース解放処理を記述
}

void EventManager::AddEvent(const GameEvent& event)
{
    // イベントをリストに追加
    events.push_back(event);
}

void EventManager::UpdateEvents()
{
    // イベントの進行状況を確認し、必要なアクションを実行
    for (size_t i = 0; i < events.size(); ++i)
    {
        if (events[i].state == EVENT_STATE_ACTIVE)
        {
            // アクティブなイベントの処理を実行
            // 必要に応じてイベントの進行状況を変更
        }
    }
}

void EventManager::CompleteEvent(int eventIndex)
{
    // イベントを完了状態に変更
    if (eventIndex >= 0 && eventIndex < events.size())
    {
        events[eventIndex].state = EVENT_STATE_COMPLETED;
    }
}

// 他のイベント管理関連のメソッドを追加
