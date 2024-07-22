#pragma once
#include "IEventListener.h"
#include "GameEvent.h"
#include "Engine/GameObject.h"
#include <vector>

class EventManager : public GameObject {
public:
    EventManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void AddEvent(const GameEvent& event);
    void UpdateEvents();
    void CompleteEvent(int eventIndex);
    void RegisterListener(IEventListener* listener);

private:
    std::vector<GameEvent> events_;
    std::vector<IEventListener*> listeners_;
};
