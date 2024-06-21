#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Player.h"
#include "Aim.h"
#include "Gun.h"
#include <algorithm>

namespace
{
    const float upLimit = 89.0f;
    const float downLimit = -89.0f;

    const int halfScreenWidth = Direct3D::screenWidth_ / 2;
    const int halfScreenHeight = Direct3D::screenHeight_ / 2;

    XMFLOAT3 FORWARD_VECTOR = { 0.0f,0.0f,1.0f };
}

// �R���X�g���N�^
Aim::Aim(GameObject* parent) : GameObject(parent, "Aim"), pNum_(nullptr), pPlayer_(nullptr),
aimDirection_{ 0,0,0 }, camPos_{0,0,0}, mouseSensitivity_{0, 0}, eyePositon_{0,0,0}
{
    // �}�E�X���x��INI�t�@�C������擾
    mouseSensitivity_.x = GetPrivateProfileFloat("MOUSE_SENSITIVITY", "X", 0, "./setup.ini");
    mouseSensitivity_.y = GetPrivateProfileFloat("MOUSE_SENSITIVITY", "Y", 0, "./setup.ini");
}

// �f�X�g���N�^
Aim::~Aim()
{
}

// ������
void Aim::Initialize()
{
    // �G�C���N���X�̌Ăяo���ʒu
    transform_.position_.y = EYE_POSITION;

    // �}�E�X���W�|�C���^�[
    pNum_ = new Text;
    pNum_->Initialize();

    // �e�̓J�����ɂ�����
    Instantiate<Gun>(this);

    // �v���C���[�I�u�W�F�N�g�擾
    pPlayer_ = static_cast<Player*>(FindObject("Player"));
    
    //�}�E�X�����ʒu(��/2, ����/2)
    Input::SetMousePosition(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2);


}

// �X�V
void Aim::Update()
{ 
    UpdateRotation();
    UpdateCameraPosition();
}

void Aim::UpdateRotation()
{
    // ���������̉�]���X�V
    transform_.rotate_.y += Input::GetMouseMove().x * mouseSensitivity_.x;

    // ���������̉�]�͏㉺�̌��E�𒴂��Ȃ��悤�ɐ���
    float newRotationX = transform_.rotate_.x + Input::GetMouseMove().y * mouseSensitivity_.y;
    transform_.rotate_.x = std::clamp(newRotationX, downLimit, upLimit);
}

void Aim::UpdateCameraPosition() 
{
    // �J�����̉�]
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mView = mRotX * mRotY;

    // �J�����ʒu�̌v�Z
    XMFLOAT3 plaPos = pPlayer_->GetPosition();
    camPos_ = { plaPos.x , plaPos.y + EYE_POSITION, plaPos.z };

    // �J�����̈ʒu�Əœ_���擾
    XMVECTOR camPosVector = XMLoadFloat3(&camPos_);
    XMVECTOR forwardVector = XMVector3TransformCoord(XMLoadFloat3(&FORWARD_VECTOR), mView);

    ///////////////�v���C���[�N���X�Ɍ��Ă��������`����
    XMStoreFloat3(&aimDirection_, forwardVector);
    ////////////////////////////////////////////////////
    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    // �J�����̈ʒu�Əœ_��ݒ�
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);

    // �J�����V�F�C�N��K�p
    if (shakeTimeLeft_ > 0)
    {
        camPosFloat3.x += ((rand() % 100) / 100.0f - 0.5f) * shakeMagnitude_ * 2;
        camPosFloat3.y += ((rand() % 100) / 100.0f - 0.5f) * shakeMagnitude_ * 2;
        camPosFloat3.z += ((rand() % 100) / 100.0f - 0.5f) * shakeMagnitude_ * 2;

        shakeTimeLeft_ -= 0.01f;
    }

    eyePositon_ = camPosFloat3;

    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}

// �`��
void Aim::Draw()
{
    // �N���X�w�A��\��
    pNum_->Draw(halfScreenWidth, halfScreenHeight, "+");
}

// �J��
void Aim::Release()
{
}

void Aim::StartCameraShake(float duration, float magnitude)
{
    shakeDuration_ = duration;
    shakeMagnitude_ = magnitude;
    shakeTimeLeft_ = duration;
}