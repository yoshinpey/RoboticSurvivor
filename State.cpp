#include "State.h"


// 待機状態
void IdleState::EnterState()
{
    pNum = new Text;
    pNum->Initialize();
    // 待機状態に入るときの初期化処理
}

void IdleState::UpdateState()
{
    pNum->Draw(100, 100, "aaaaaaaaaaaaaaaaa");
    // 待機状態の更新処理
}

void IdleState::ExitState()
{
    // 待機状態から出るときの後処理
}



// 歩行状態
void WalkingState::EnterState()
{
    // 歩行状態に入るときの初期化処理
}

void WalkingState::UpdateState()
{
    // 歩行状態の更新処理
}

void WalkingState::ExitState()
{
    // 歩行状態から出るときの後処理
}



// 走行状態
void RunningState::EnterState()
{
    // 走行状態に入るときの初期化処理
}

void RunningState::UpdateState()
{
    // 走行状態の更新処理
}

void RunningState::ExitState()
{
    // 走行状態から出るときの後処理
}



// 跳躍状態
void JumpingState::EnterState()
{
    // 跳躍状態に入るときの初期化処理
}

void JumpingState::UpdateState()
{
    // 跳躍状態の更新処理
}

void JumpingState::ExitState()
{
    // 跳躍状態から出るときの後処理
}
