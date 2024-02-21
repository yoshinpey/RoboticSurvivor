#pragma once
#include "StateBase.h"
#include <string>
#include <map>

class GameObject;

// ��ԑJ�ڂ��Ǘ�����N���X
class StateManager
{
private:
    std::map<std::string, StateBase*> statesMap_;     // ��Ԃ𖼑O�ŊǗ�����}�b�v
    StateBase* currentState_;
    GameObject* pParent_;

public:
    StateManager(GameObject* parent);
    ~StateManager();

    void Initialize();
    void Update();
    void ChangeState(const std::string& stateName);                         // ��Ԃ̖��O���󂯎��
    StateBase* AddState(const std::string& stateName, StateBase* state);    // ���O�ƑΉ�����C���X�^���X��ǉ�
    GameObject* GetGameobject() { return pParent_; }
};
