#pragma once

// 状態ベースクラス
class StateBase
{
public:
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

    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 歩行状態
class WalkingState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 走行状態
class RunningState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

// 跳躍状態
class JumpingState : public StateBase
{
public:
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};
