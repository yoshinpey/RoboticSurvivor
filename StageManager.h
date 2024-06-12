#pragma once
#include <vector>
#include "StageBase.h"

class StageManager
{
    std::vector<StageBase*> stages_;  // �X�e�[�W�I�u�W�F�N�g�̃��X�g
    GameObject* pParent_;
public:
    StageManager(GameObject* parent);
    ~StageManager();

    // �X�e�[�W�̐������s��
    void CreateStage(XMFLOAT3 setPosition, StageType stageType);

    // �w�肵����ނ̃X�e�[�W���폜
    void RemoveStage(StageType enemyType);

    // �s�v�ɂȂ����X�e�[�W�����X�g����폜����
    void RemoveCompletedStages(StageBase* stage);

    // ���ׂẴX�e�[�W�̍폜���s��
    void RemoveAllStages();

    // �X�e�[�W���X�g���擾����
    std::vector<StageBase*> GetStageList() { return stages_; }
};