#include "StageManager.h"

#include "Stage_Floor.h"
#include "Stage_Skybox.h"

StageManager::StageManager(GameObject* parent)
	: pParent_(parent), stages_()
{
}

StageManager::~StageManager()
{
	// �X�e�[�W�̉��(�Q�[���I�u�W�F�N�g�ł���Ă邩��f���[�g�͕s�v)
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
    // ��v����Stage��S�폜
    for (auto it = stages_.begin(); it != stages_.end(); )
    {
        if ((*it)->GetStageType() == stageType)
        {
            (*it)->KillMe();        // Stage�{�̂��폜
            it = stages_.erase(it); // ���X�g����폜
        }
        else
        {
            ++it;
        }
    }
}

void StageManager::RemoveCompletedStages(StageBase* stage)
{
    // �s�v�ɂȂ����X�e�[�W���}�l�[�W���[���̃��X�g����폜����
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
    // �S�ẴX�e�[�W�I�u�W�F�N�g���폜����
    for (auto stage : stages_)
    {
        stage->KillMe();
    }
    // �X�e�[�W���X�g���N���A����
    stages_.clear();
}

