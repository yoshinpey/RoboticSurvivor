#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Text.h"

#include "StateManager.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"
#include "Ground.h"
#include "PlayerState.h"

//�R���X�g���N�^
Player::Player(GameObject* parent) : PlayerBase(parent, "Player"),
    pText_(nullptr), pStateManager_(nullptr), pAim_(nullptr),
    gravity_(-1), jumping_(false), nowHp_(0), jumpDelta_(0.01f), velocity_(0.0f, 0.0f, 0.0f),
    movement_(0.0f, 0.0f, 0.0f), acceleration_(0.03f), friction_(0.85f), jumpFriction_(1.15f)
{
    // �p�����[�^���Z�b�g
    parameter_.walkSpeed_       = GetPrivateProfileFloat("Parameter", "walkSpeed", 0, "Settings/PlayerSettings.ini");
    parameter_.runSpeed_        = GetPrivateProfileFloat("Parameter", "runSpeed", 0, "Settings/PlayerSettings.ini");
    parameter_.jumpVelocity_    = GetPrivateProfileFloat("Parameter", "jumpHeight", 0, "Settings/PlayerSettings.ini");

    // �X�e�[�^�X���Z�b�g
    status_.maxHp_              = GetPrivateProfileFloat("Status", "maxHp", 0, "Settings/PlayerSettings.ini");
    nowHp_ = status_.maxHp_;    // ���݂�HP���ő�l�ŏ�����

    // �X�e�[�g�}�l�[�W���[
    pStateManager_ = new StateManager(this);

    //�e�L�X�g
    pText_ = new Text;

}

//�f�X�g���N�^
Player::~Player()
{
    SAFE_DELETE(pStateManager_);
}

//������
void Player::Initialize()
{
    pText_->Initialize();

    //���_�N���X�ǂݍ���
    InstantiateFront<Aim>(this);
    pAim_ = (Aim*)FindObject("Aim");

    //�X�e�[�W�I�u�W�F�N�g��T��
    //Ground* pGround = (Ground*)FindObject("Ground");
    //hGroundModel_ = pGround->GetModelHandle();

    // ���炩���ߏ�ԃC���X�^���X�𐶐����ēo�^
    pStateManager_->AddState("IdleState", new PlayerIdleState(pStateManager_));
    pStateManager_->AddState("WalkingState", new PlayerWalkingState(pStateManager_));
    pStateManager_->AddState("RunningState", new PlayerRunningState(pStateManager_));
    pStateManager_->AddState("JumpingState", new PlayerJumpingState(pStateManager_));

    // �������
    pStateManager_->ChangeState("IdleState");
}

//�X�V
void Player::Update()
{
    // �X�e�[�g�}�l�[�W���[�̍X�V
    pStateManager_->Update();

    if (jumping_)
    {
        ApplyGravity();
    }
}

//�`��
void Player::Draw()
{
    //�f�o�b�N�p
    pText_->Draw(1150, 100, "X:");
    pText_->Draw(1200, 100, (int)transform_.position_.x);
    pText_->Draw(1150, 250, "Y:");
    pText_->Draw(1200, 250, (int)transform_.position_.y);
    pText_->Draw(1150, 400, "Z:");
    pText_->Draw(1200, 400, (int)transform_.position_.z);
}

//�J��
void Player::Release()
{
    SAFE_DELETE(pText_);
}

//�v���C���[��HP
void Player::PlayerHitPoint()
{
    //////////////////UI�}�l�[�W���[�o�R�ɕύX�\��B
    //HP�Q�[�W�Ăяo��
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(status_.maxHp_, nowHp_);

    //�f�o�b�O�p
    if (Input::IsKeyDown(DIK_M))
    {
        nowHp_ += 20.0f;
        if (nowHp_ > status_.maxHp_)
        {
            nowHp_ = status_.maxHp_;
        }
    }
    if (Input::IsKeyDown(DIK_N))
    {
        nowHp_ -= 20.0f;
        if (nowHp_ < 0.0f)
        {
            nowHp_ = 0.0f;
        }
    }
}

void Player::Walk()
{
    ApplyMovement(CalculateMoveInput(), parameter_.walkSpeed_);
}

void Player::Run()
{
    ApplyMovement(CalculateMoveInput(), parameter_.runSpeed_);
}

// �ړ��ɔ��f����֐�
void Player::ApplyMovement(const XMFLOAT3& moveVector, float speed)
{
    // ���݂̑��x
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&movement_)));

    // �ő呬�x�𒴂��Ă����琳�K���A�ő�l�̒l�ɂ���
    if (currentSpeed > speed)
    {
        XMVECTOR vMove = XMLoadFloat3(&movement_);
        vMove = XMVector3Normalize(vMove);
        vMove *= speed;
        XMStoreFloat3(&movement_, vMove);
    }

    // �ړ��ɔ��f
    movement_.x += moveVector.x * acceleration_;
    movement_.z += moveVector.z * acceleration_;


    // �ړ��ʂ�K�p
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;

}

// ������K�p����֐�
void Player::ApplyDeceleration()
{
    // �؋󒆂͌����W����ς���
    if (jumping_)
    {
        movement_.x *= friction_ * jumpFriction_;
        movement_.z *= friction_ * jumpFriction_;
    }
    else
    {
        movement_.x *= friction_;
        movement_.z *= friction_;
    }

    // �ړ��ɔ��f
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;
}

// �W�����v
void Player::Jump()
{
    if (jumping_) return;

    // �ړ��������擾
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // �ړ��������W�����v�̕����Ƃ��ēK�p
    velocity_.x = parameter_.jumpVelocity_ * moveDirection.x;
    velocity_.y = parameter_.jumpVelocity_;
    velocity_.z = parameter_.jumpVelocity_ * moveDirection.z;

    //�f�o�b�N�p
    OutputDebugStringA(std::to_string(parameter_.jumpVelocity_).c_str());
    OutputDebugString("\n");

    // �W�����v�ł��Ȃ�����
    jumping_ = true;
}

// �ړ��v�Z���s���֐�
XMFLOAT3 Player::CalculateMoveInput()
{
    // �v�Z���ʓ����p
    XMFLOAT3 moveDirection = XMFLOAT3(0.0f, 0.0f, 0.0f);

    // �G�C�����Ăяo��
    XMFLOAT3 aimDirection = pAim_->GetAimDirection();

    // Player�N���X��Move�֐����̈ꕔ
    if (InputManager::IsMoveForward())
    {
        moveDirection.x += aimDirection.x;
        moveDirection.z += aimDirection.z;
    }
    if (InputManager::IsMoveLeft())
    {
        moveDirection.x -= aimDirection.z;
        moveDirection.z += aimDirection.x;
    }
    if (InputManager::IsMoveBackward())
    {
        moveDirection.x -= aimDirection.x;
        moveDirection.z -= aimDirection.z;
    }
    if (InputManager::IsMoveRight())
    {
        moveDirection.x += aimDirection.z;
        moveDirection.z -= aimDirection.x;
    }

    // ���K��
    NormalizeFloat3(moveDirection);

    return moveDirection;
}

void Player::ApplyGravity()
{
    velocity_.y += gravity_ * jumpDelta_;
    transform_.position_.y += velocity_.y;

    // �n�ʂɓ��B������W�����v�\�ȏ�Ԃɖ߂�
    if (transform_.position_.y <= 0)
    {
        transform_.position_.y = 0;
        jumping_ = false;
        velocity_.y = 0;
    }
}

//bool Player::RayCastStage(XMFLOAT3 position)
//{
//    if (!useRayCast_) return false;
//
//    RayCastData data;
//    data.start = position;                  // ���C�̔��ˍ��W
//    data.start.y = 0;                       // ���C�̔��ˈʒu
//    data.dir = { 0, -1, 0 };                // ���C�̕���
//    Model::RayCast(hGroundModel_, &data);
//
//    // ����������A�������ʒu��������
//    if (data.hit) 
//    { 
//        transform_.position_.y = -data.dist; 
//        return true;
//    }
//    return false;
//}