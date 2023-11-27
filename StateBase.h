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
