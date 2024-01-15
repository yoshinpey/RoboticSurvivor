#pragma once
#include "State.h"
#include <unordered_map>

class GameObject;

// 状態遷移を管理するクラス
class StateManager
{
private:
    std::unordered_map<std::string, StateBase*> statesMap_;     // 状態を名前で管理するマップ
    StateBase* currentState_;
    GameObject* gameObj_;

public:
    StateManager(GameObject* gameObj);
    ~StateManager();

    void Initialize();
    void Update();
    void ChangeState(const std::string& stateName);                         // 状態の名前を受け取る
    StateBase* AddState(const std::string& stateName, StateBase* state);    // 名前と対応するインスタンスを追加
    GameObject* GetGameobject() { return gameObj_; }
};
