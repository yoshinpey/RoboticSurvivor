#pragma once
#include "Engine/GameObject.h"

class EffectManager : public GameObject
{
public:
    EffectManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // �G�t�F�N�g�֘A�̃��\�b�h��ǉ�

private:
    // �G�t�F�N�g�f�[�^���Ǘ����邽�߂̃R���e�i�Ȃǂ�錾
};
