#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Player.h"
#include "Aim.h"
#include "Gun.h"
#include <algorithm>

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
    transform_.rotate_.x = std::clamp(newRotationX, -89.0f, 89.0f);
}

void Aim::UpdateCameraPosition() 
{
    // �J�����̉�]
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mView = mRotX * mRotY;

    // �J�����ʒu�̌v�Z
    XMFLOAT3 playerPos = pPlayer_->GetPosition();
    camPos_.x = playerPos.x;
    camPos_.y = playerPos.y + EYE_POSITION; // �ڐ��̍���
    camPos_.z = playerPos.z;

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

    eyePositon_ = camPosFloat3;

    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}

// �`��
void Aim::Draw()
{
    // �N���X�w�A��\��
    pNum_->Draw(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2, "+");
}

// �J��
void Aim::Release()
{
}

