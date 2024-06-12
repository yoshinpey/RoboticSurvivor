#pragma once
#include "Engine/GameObject.h"

// �X�e�[�W�̎��
enum class StageType
{
    FLOOR,
    SKYBOX,
    MAX
};

// �X�e�[�W�I�u�W�F�N�g�̂��ƂɂȂ�N���X
class StageBase : public GameObject
{
protected:
    StageType stageType_; // �X�e�[�W�̎��

public:
    StageBase(GameObject* parent, StageType stageType, std::string name)
        : GameObject(parent, name), stageType_(stageType) 
    {
    }

    virtual ~StageBase() = default;

    // �X�e�[�W�̎�ނ��擾
    StageType GetStageType() const { return stageType_; }
};