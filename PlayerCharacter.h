#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class PlayerCharacter : public GameObject
{
public:
    PlayerCharacter(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override; // �h���[�֐���ǉ�
    void Release() override;

    // �v���C���[�L�����N�^�[�̍s���𐧌䂷�郁�\�b�h��ǉ�

private:
    // �v���C���[�L�����N�^�[�̃X�e�[�^�X��A�N�V�����ɕK�v�ȕϐ���錾
};
