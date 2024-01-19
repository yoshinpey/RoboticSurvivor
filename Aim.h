#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

#include "Player.h"

// ���_���Ǘ�����N���X
class Aim : public GameObject
{
    static const float EYE_POSITION;
    static const float MOUSE_SENSITIVITY_X;
    static const float MOUSE_SENSITIVITY_Y;

    XMFLOAT3 aimDirection_;
    XMFLOAT3 camPos_;
    XMFLOAT3 eyePositon_;
    XMFLOAT2 mouseSensitivity_;
    Text* pNum_;
    Player* pPlayer_;

    void UpdateRotation();
    void UpdateCameraPosition();

public:
    Aim(GameObject* parent);        //�R���X�g���N�^
    ~Aim();                         //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    //�i�s�����x�N�g����Aim�����擾
    XMFLOAT3 GetAimDirection(){ return aimDirection_; }
    XMFLOAT3 GetEyePosition(){ return eyePositon_; }
};