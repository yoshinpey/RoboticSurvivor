#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class WeaponManager : public GameObject
{
public:
    WeaponManager(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // ����֘A�̃��\�b�h��ǉ�

private:
    // ����f�[�^���Ǘ����邽�߂̃R���e�i�Ȃǂ�錾
};
