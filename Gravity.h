#pragma once
#include "Engine/GameObject.h"

//  �d�͂��Ǘ�����N���X
class Gravity : public GameObject
{
private:
    float gravity_;                 //�d��
public:
    Gravity(GameObject* parent);    //�R���X�g���N�^
    ~Gravity();                     //�f�X�g���N�^

    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    //�d�̓Z�b�g
    float AddGravity(float _transPosY)
    {
        return (_transPosY += gravity_);
    }
};