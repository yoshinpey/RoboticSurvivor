#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class UIManager : public GameObject
{
public:
    UIManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Release() override;

    // UI�֘A�̃��\�b�h��ǉ�

private:
    // UI�v�f���Ǘ����邽�߂̃R���e�i�Ȃǂ�錾
};
