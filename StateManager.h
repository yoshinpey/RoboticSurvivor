#pragma once
#include "State.h"

class GameObject;

// ó‘Ô‘JˆÚ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class StateManager
{
private:
    StateBase* currentState_;
    GameObject* gameObj_;

public:
    StateManager(GameObject* gameObj);
    ~StateManager();

    void Initialize();
    void Update();
    void ChangeState(StateBase* newState);
    GameObject* GetGameobject() { return gameObj_; }
};
