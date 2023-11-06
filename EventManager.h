#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

enum EVENT_STATE
{
    EVENT_STATE_INACTIVE,
    EVENT_STATE_ACTIVE,
    EVENT_STATE_COMPLETED,
};

struct GameEvent
{
    EVENT_STATE state;
    std::string description;
    // 他のイベントデータを追加
};

class EventManager : public GameObject
{
public:
    EventManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void AddEvent(const GameEvent& event);
    void UpdateEvents();
    void CompleteEvent(int eventIndex);

    // 他のイベント管理関連のメソッドを追加

private:
    std::vector<GameEvent> events;
};
