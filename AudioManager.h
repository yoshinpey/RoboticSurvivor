#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class AudioManager : public GameObject
{
public:
    AudioManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Release() override;

    // �I�[�f�B�I�֘A�̃��\�b�h��ǉ�

private:
    // �I�[�f�B�I�f�[�^���Ǘ����邽�߂̃R���e�i�Ȃǂ�錾
};
