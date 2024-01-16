#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

#include "Player.h"

//���_���Ǘ�����N���X
class Aim : public GameObject
{
    XMFLOAT3 plaPos_;                       //�v���C���[�ʒu
    XMFLOAT3 camPos_;                       //�J���� �ʒu,�œ_
    Text* pNum_;                            //�e�L�X�g
    Player* pPlayer_;                       //�v���C���[�C���X�^���X
    XMFLOAT3 aimDirection_;                 //���݂̎��_�Ɋ�Â����i�s�����x�N�g��
    XMFLOAT2 mouseSensitivity_;             //�}�E�X�̊��x
    const float MOUSE_SENSITIVITY_X = 0.05f;
    const float MOUSE_SENSITIVITY_Y = 0.05f;
    
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