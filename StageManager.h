#pragma once
#include <vector>
#include "StageBase.h"

class StageManager
{
    std::vector<StageBase*> stages_;  // ステージオブジェクトのリスト
    GameObject* pParent_;
public:
    StageManager(GameObject* parent);
    ~StageManager();

    // ステージの生成を行う
    void CreateStage(XMFLOAT3 setPosition, StageType stageType);

    // 指定した種類のステージを削除
    void RemoveStage(StageType enemyType);

    // 不要になったステージをリストから削除する
    void RemoveCompletedStages(StageBase* stage);

    // すべてのステージの削除を行う
    void RemoveAllStages();

    // ステージリストを取得する
    std::vector<StageBase*> GetStageList() { return stages_; }
};