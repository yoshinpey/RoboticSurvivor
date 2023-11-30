#pragma once
#include "Engine/Text.h"

class StateManager;

// 状態ベースクラス
class StateBase
{   
protected:
    Text* pNum;                 // テキスト
    StateManager* pStateManager_;
public:
    StateBase(StateManager* manager) : pStateManager_(manager) {}

    // デストラクタ
    virtual ~StateBase() {};
    // 状態に入るときの初期化
    virtual void EnterState() = 0;
    // 状態の更新
    virtual void UpdateState() = 0;
    // 状態から出るときの後処理
    virtual void ExitState() = 0;
};

// 待機状態
class IdleState : public StateBase
{
public:
    IdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 歩行状態
class WalkingState : public StateBase
{
public:
    WalkingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 走行状態
class RunningState : public StateBase
{
public:
    RunningState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 跳躍状態
class JumpingState : public StateBase
{
public:
    JumpingState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
