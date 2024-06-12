#include "StageManager.h"

#include "Stage_Floor.h"
#include "Stage_Skybox.h"

StageManager::StageManager(GameObject* parent)
	: pParent_(parent), stages_()
{
}

StageManager::~StageManager()
{
	// ステージの解放(ゲームオブジェクトでやってるからデリートは不要)
    stages_.clear();
}

void StageManager::CreateStage(XMFLOAT3 setPosition, StageType stageType)
{
    StageBase* pNewStage = nullptr;
    switch (stageType)
    {
    case StageType::FLOOR:
        pNewStage = Instantiate<Stage_Floor>(pParent_);
        break;

    case StageType::SKYBOX:
        pNewStage = Instantiate<Stage_Skybox>(pParent_);
        break;

    case StageType::MAX:
        return;
    }
    pNewStage->SetPosition(setPosition);
    stages_.push_back(pNewStage);
}

void StageManager::RemoveStage(StageType stageType)
{
    // 一致するStageを全削除
    for (auto it = stages_.begin(); it != stages_.end(); )
    {
        if ((*it)->GetStageType() == stageType)
        {
            (*it)->KillMe();        // Stage本体を削除
            it = stages_.erase(it); // リストから削除
        }
        else
        {
            ++it;
        }
    }
}

void StageManager::RemoveCompletedStages(StageBase* stage)
{
    // 不要になったステージをマネージャー内のリストから削除する
    for (auto it = stages_.begin(); it != stages_.end(); )
    {
        if ((*it) == stage)
        {
            it = stages_.erase(it);
            return;
        }
        else
        {
            ++it;
        }
    }
}

void StageManager::RemoveAllStages()
{
    // 全てのステージオブジェクトを削除する
    for (auto stage : stages_)
    {
        stage->KillMe();
    }
    // ステージリストをクリアする
    stages_.clear();
}

