#pragma once
#include "Engine/global.h"
#include "Engine/GameObject.h"

class PlayerCamera : public GameObject
{
public:
    PlayerCamera(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override; // �J�����̕`�揈���i�K�v�ȏꍇ�ɋL�q�j
    void Release() override;

    // �J��������ɕK�v�ȃ��\�b�h��ǉ�

private:
    // �J�����̃v���p�e�B���Ԃ�ێ�����ϐ���錾
};
