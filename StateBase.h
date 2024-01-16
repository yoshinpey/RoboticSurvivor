#pragma once

class StateManager;
class Player;

// 状態ベースクラス
class StateBase
{   
protected:
    StateManager* pStateManager_;
    Player* pPlayer_;
public:
    StateBase(StateManager* manager) 
        : pStateManager_(manager), pPlayer_(nullptr)
    {
    }

    // デストラクタ
    virtual ~StateBase() {};
    // 状態に入るときの初期化
    virtual void EnterState() = 0;
    // 状態の更新
    virtual void UpdateState() = 0;
    // 状態から出るときの後処理
    virtual void ExitState() = 0;
};