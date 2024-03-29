#pragma once
#include "StateBase.h"
#include <string>
#include <map>

class GameObject;

// 状態遷移を管理するクラス
class StateManager
{
private:
    std::map<std::string, StateBase*> statesMap_;     // 状態を名前で管理するマップ
    StateBase* currentState_;
    GameObject* pParent_;

public:
    StateManager(GameObject* parent);
    ~StateManager();

    void Update();
    void ChangeState(const std::string& stateName);                         // 状態の名前を受け取る
    StateBase* AddState(const std::string& stateName, StateBase* state);    // 名前と対応するインスタンスを追加
    GameObject* GetGameobject() { return pParent_; }
};
