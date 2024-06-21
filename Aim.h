#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

class Player;

// ���_���Ǘ�����N���X
class Aim : public GameObject
{
    const float EYE_POSITION = 2.0f;

    XMFLOAT3 aimDirection_;
    XMFLOAT3 camPos_;
    XMFLOAT3 eyePositon_;
    XMFLOAT2 mouseSensitivity_;
    Text* pNum_;
    Player* pPlayer_;

    // �J�����V�F�C�N�p�̃p�����[�^
    float shakeDuration_;
    float shakeMagnitude_;
    float shakeTimeLeft_;

    void UpdateRotation();
    void UpdateCameraPosition();

public:
    Aim(GameObject* parent);        //�R���X�g���N�^
    ~Aim();                         //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
    
    // �J�����V�F�C�N���J�n���郁�\�b�h
    void StartCameraShake(float duration, float magnitude);

    //�i�s�����x�N�g����Aim�����擾
    XMFLOAT3 GetAimDirection(){ return aimDirection_; }
    XMFLOAT3 GetEyePosition(){ return eyePositon_; }
};