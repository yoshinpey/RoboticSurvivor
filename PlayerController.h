#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class PlayerController : public GameObject
{
public:
    PlayerController(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Release() override;

    // �v���C���[�̍s���𐧌䂷�郁�\�b�h��ǉ�

private:
    // �v���C���[�̍s���ɕK�v�ȕϐ���I�u�W�F�N�g��錾
};
