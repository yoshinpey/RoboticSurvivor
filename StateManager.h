#pragma once
#include "State.h"

class GameObject;

// ��ԑJ�ڂ��Ǘ�����N���X
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
