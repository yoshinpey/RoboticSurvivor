#pragma once
#include "IEventListener.h"
#include "GameEvent.h"
#include "Engine/GameObject.h"
#include <vector>

class EventManager : public GameObject
{
public:
    EventManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void AddEvent(const GameEvent& event);
    void AddListener(IEventListener* listener);
    void NotifyListeners(const GameEvent& event);

private:
    std::vector<GameEvent> events_;
    std::vector<IEventListener*> listeners_;

    void UpdateEvents();
};
