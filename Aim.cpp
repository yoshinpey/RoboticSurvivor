#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Gun.h"

const float Aim::EYE_POSITION = 2.0f;
const float Aim::MOUSE_SENSITIVITY_X = 0.05f;
const float Aim::MOUSE_SENSITIVITY_Y = 0.05f;

// �R���X�g���N�^
Aim::Aim(GameObject* parent) : GameObject(parent, "Aim"), pNum_(nullptr), pPlayer_(nullptr),
aimDirection_{ 0,0,0 }, camPos_{0,0,0}, mouseSensitivity_ {MOUSE_SENSITIVITY_X, MOUSE_SENSITIVITY_Y}
{
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

    // �}�E�X���W�e�L�X�g
    pNum_ = new Text;
    pNum_->Initialize();

    // �e�̓J�����ɂ�����
    Instantiate<Gun>(this);

    //�}�E�X�����ʒu(��/2, ����/2)
    Input::SetMousePosition(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2);

    // �v���C���[�I�u�W�F�N�g�擾
    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

// �X�V
void Aim::Update()
{ 
    UpdateRotation();
    UpdateCameraPosition();
}

void Aim::UpdateRotation() 
{
    XMFLOAT3 mouseMove = Input::GetMouseMove();
    transform_.rotate_.y += mouseMove.x * mouseSensitivity_.x;
    transform_.rotate_.x += mouseMove.y * mouseSensitivity_.y;
}

void Aim::UpdateCameraPosition() 
{
    // �J�����̉�]
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mView = mRotX * mRotY;

    XMFLOAT3 plaPos = pPlayer_->GetPlaPos();

    // �J�����ʒu�̌v�Z
    camPos_.x = plaPos.x;
    camPos_.y = plaPos.y + EYE_POSITION; // �ڐ��̍���
    camPos_.z = plaPos.z;

    // �J�����̈ʒu�Əœ_���擾
    XMVECTOR camPosVector = XMLoadFloat3(&camPos_);
    XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forwardVector = XMVector3TransformCoord(forwardVector, mView);
    XMStoreFloat3(&aimDirection_, forwardVector); //�v���C���[�N���X�ɐi�s�����x�N�g��(float3)��`����

    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    // �J�����̈ʒu�Əœ_��ݒ�
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);

    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}
// �`��
void Aim::Draw()
{
    pNum_->Draw(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2, "+");
}

// �J��
void Aim::Release()
{
}

