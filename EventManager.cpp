
#include "EventManager.h"

EventManager::EventManager(GameObject* parent)
    : GameObject(parent, "EventManager")
{
}

void EventManager::Initialize()
{
    // イベントの初期化処理
}

void EventManager::Update()
{
    UpdateEvents();
}

void EventManager::Draw()
{
    // イベントの描画処理
}

void EventManager::Release()
{
    // イベントのリソース解放処理
}

void EventManager::AddEvent(const GameEvent& event)
{
    events_.push_back(event);
}

void EventManager::AddListener(IEventListener* listener)
{
    listeners_.push_back(listener);
}

void EventManager::NotifyListeners(const GameEvent& event)
{
    for (auto listener : listeners_)
    {
        listener->OnEvent(event);
    }
}

void EventManager::UpdateEvents()
{
    for (auto& event : events_)
    {
        if (event.state == EVENT_STATE_ACTIVE && event.condition())
        {
            event.action();
            event.state = EVENT_STATE_COMPLETED;
            NotifyListeners(event);
        }
    }
}