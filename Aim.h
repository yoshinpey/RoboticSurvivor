#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//���_���Ǘ�����N���X
class Aim : public GameObject
{
    float screenWidth_, screenHeight_;
    XMFLOAT3 plaPos_;                       //�v���C���[�ʒu
    XMFLOAT3 camPos_, camTarget_;           //�J���� �ʒu,�œ_
    Text* pNum_;                            //�e�L�X�g
    XMFLOAT3 aimDirection_;                 //���݂̎��_�Ɋ�Â����i�s�����x�N�g��
public:
    Aim(GameObject* parent);        //�R���X�g���N�^
    ~Aim();                         //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    //�i�s�����x�N�g����Aim�����擾
    XMFLOAT3 GetAimDirection(){ return aimDirection_; }
};