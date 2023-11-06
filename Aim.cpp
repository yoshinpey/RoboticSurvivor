#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Player.h"
#include "Gun.h"


//�R���X�g���N�^
Aim::Aim(GameObject* parent)
    :GameObject(parent, "Aim"), pNum_(nullptr),
    plaPos_{ 0,0,0 }, camPos_{ 0,0,0 }, camTarget_{ 0,0,0 }, aimDirection_{ 0,0,0 }
{
}

//�f�X�g���N�^
Aim::~Aim()
{
}

//������
void Aim::Initialize()
{
    //�G�C���N���X�̌Ăяo���ʒu
    transform_.position_.y = 2;

    //�}�E�X���W�e�L�X�g
    pNum_ = new Text;
    pNum_->Initialize();

    //�e�̓J�����ɂ�
    Instantiate<Gun>(this);

    //�}�E�X�����ʒu(��/2, ����/2)
    Input::SetMousePosition(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2);

}

//�X�V
void Aim::Update()
{ 
    //�}�E�X�ړ���
    XMFLOAT3 mouseMove = Input::GetMouseMove(); // �}�E�X�̈ړ��ʂ��擾

    //�ړ��ʂ����Z
    transform_.rotate_.y += (mouseMove.x) * 0.05f; // �������̉�]
    transform_.rotate_.x += (mouseMove.y) * 0.05f; // �c�����̉�]

    ////�J�����̉�]
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); 

    //�J�����̈ʒu�Ɖ�]������
    XMMATRIX mView = mRotX * mRotY;

    //�v���C���[���W�擾
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    plaPos_ = pPlayer->GetPlaPos();

    //�v���C���[�L�����N�^�[�̈ʒu���J�����̈ʒu�Ƃ���
    camPos_.x = plaPos_.x;
    camPos_.y = plaPos_.y + 2; //�ڐ�����
    camPos_.z = plaPos_.z;

    //�J�����̈ʒu�Əœ_���擾
    XMVECTOR camPosVector = XMLoadFloat3(&camPos_);
    XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forwardVector = XMVector3TransformCoord(forwardVector, mView);
    XMStoreFloat3(&aimDirection_, forwardVector);   //�v���C���[�N���X�ɐi�s�����x�N�g��(float3)��`����p                    
    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    //�J�����̈ʒu�Əœ_��ݒ�
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);
    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}

//�`��
void Aim::Draw()
{
    pNum_->Draw(Direct3D::screenWidth_ /2, Direct3D::screenHeight_ /2, "+");
}

//�J��
void Aim::Release()
{
}
