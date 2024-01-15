#pragma once
#include "State.h"
#include <unordered_map>

class GameObject;

// ��ԑJ�ڂ��Ǘ�����N���X
class StateManager
{
private:
    std::unordered_map<std::string, StateBase*> statesMap_;     // ��Ԃ𖼑O�ŊǗ�����}�b�v
    StateBase* currentState_;
    GameObject* gameObj_;

public:
    StateManager(GameObject* gameObj);
    ~StateManager();

    void Initialize();
    void Update();
    void ChangeState(const std::string& stateName);                 // ��Ԃ̖��O���󂯎��
    void AddState(const std::string& stateName, StateBase* state);  // ��Ԃ̖��O�ƑΉ�����C���X�^���X��ǉ�
    GameObject* GetGameobject() { return gameObj_; }
};
