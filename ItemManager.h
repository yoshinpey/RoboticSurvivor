#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class ItemManager : public GameObject
{
public:
    ItemManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // �A�C�e���֘A�̃��\�b�h��ǉ�

private:
    // �A�C�e���f�[�^���Ǘ����邽�߂̃R���e�i�Ȃǂ�錾
};
