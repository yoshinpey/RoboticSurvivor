#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "Aim.h"
#include "Player.h"
#include "Gauge.h"


//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr),
    gravity_(-1), canJump_(true), maxHp_(100), nowHp_(100), jumpVelocity_(JUMP_HEIGHT), jumpDelta_(0.08f), velocity_(0.0f, 0.0f, 0.0f),
    walkSpeed_(WALK_SPEED), runSpeed_(RUN_SPEED), isMoving_(false), movement_(0.0f, 0.0f, 0.0f), acceleration_(0.05f), friction_(0.8f), moveDelta_(0.1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Human_only.fbx");
    assert(hModel_ >= 0);

    //���_�N���X�ǂݍ���
    Instantiate<Aim>(this);

    //�e�L�X�g
    pNum = new Text;
    pNum->Initialize();
}

//�X�V
void Player::Update()
{
    Move();                 //����
    Jump();                 //�W�����v�A�N�V����
    PlayerHitPoint();       //HP
}

//�`��
void Player::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�f�o�b�N�p�e�L�X�g
    pNum->Draw(1150, 100, "X:");
    pNum->Draw(1200, 100, (int)transform_.position_.x);
    pNum->Draw(1150, 250, "Y:");
    pNum->Draw(1200, 250, (int)transform_.position_.y);
    pNum->Draw(1150, 400, "Z:");
    pNum->Draw(1200, 400, (int)transform_.position_.z);
}

//�J��
void Player::Release()
{
}

//�v���C���[��HP
void Player::PlayerHitPoint()
{
    //HP�Q�[�W�Ăяo��
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(maxHp_, nowHp_);

    //�G���[�ׂ�
    if (Input::IsKeyDown(DIK_M))
    {
        nowHp_ += 20;
        if (nowHp_ > maxHp_)
        {
            nowHp_ = maxHp_;
        }
    }
    if (Input::IsKeyDown(DIK_N))
    {
        nowHp_ -= 20;
        if (nowHp_ < 0)
        {
            nowHp_ = 0;
        }
    }
}

// �v���C���[�̈ړ�
void Player::Move()
{
    // �ړ�
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    // �G�C�����Ăяo��
    Aim* pAim = (Aim*)FindObject("Aim");
    XMFLOAT3 aimDirection = pAim->GetAimDirection();

    // Player�N���X��Move�֐����̈ꕔ
    if (InputManager::IsMoveForward())
    {
        fMove.x += aimDirection.x;
        fMove.z += aimDirection.z;
    }
    if (InputManager::IsMoveLeft())
    {
        fMove.x -= aimDirection.z;
        fMove.z += aimDirection.x;
    }
    if (InputManager::IsMoveBackward())
    {
        fMove.x -= aimDirection.x;
        fMove.z -= aimDirection.z;
    }
    if (InputManager::IsMoveRight())
    {
        fMove.x += aimDirection.z;
        fMove.z -= aimDirection.x;
    }

    // ���K������
    float moveLength = sqrtf(fMove.x * fMove.x + fMove.z * fMove.z);

    // �[������Ȃ��������v�Z
    if (moveLength != 0)
    {
        fMove.x /= moveLength;
        fMove.z /= moveLength;
    }

    // �ړ����͂�����Ƃ��͐^
    isMoving_ = InputManager::IsMoveForward() || InputManager::IsMoveLeft() || InputManager::IsMoveBackward() || InputManager::IsMoveRight();

    // ���݂̑��x
    float currentSpeed = 0.0f;

    // �ړ����͂���
    if (isMoving_)
    {
        // �����Ă��邩�ǂ���
        if (InputManager::IsRun())
        {
            currentSpeed = runSpeed_;    // ���葬�x�ɐݒ�
        }
        else
        {
            currentSpeed = walkSpeed_;   // �������x�ɐݒ�
        }

        // ���݂̑��x��ڕW�̑��x�ɏ��X�ɋ߂Â���
        if (currentSpeed > velocity_.x)
        {
            velocity_.x += acceleration_;
            velocity_.z += acceleration_;
        }
        else
        {
            velocity_.x = currentSpeed;
            velocity_.z = currentSpeed;
        }

        // �ړ��ɔ��f
        movement_.x += fMove.x * velocity_.x * moveDelta_;
        movement_.z += fMove.z * velocity_.z * moveDelta_;

        // �ړ��ʂ�K�p
        transform_.position_.x += movement_.x;
        transform_.position_.z += movement_.z;
    }
    else
    {
        // �e�ړ��{�^���𗣂����Ƃ��Ɍ�����K��
        movement_.x *= friction_;
        movement_.z *= friction_;

        // �ړ��ɔ��f
        transform_.position_.x += movement_.x;
        transform_.position_.z += movement_.z;
    }
}

// �W�����v
void Player::Jump()
{
    // �W�����v�L�[��������Ă���A�W�����v�\�ȏꍇ
    if (InputManager::IsJump() && canJump_)
    {
        // �W�����v�J�n���ɏ����x��^����
        velocity_.y = jumpVelocity_;

        // �A���W�����v��h�~
        canJump_ = false;
    }

    // �؋�
    if (!canJump_)
    {
        // �����h�ւ̈ړ�����
        transform_.position_.y += velocity_.y * jumpDelta_;

        // �d�͂�K�p���ăW�����v�̍����𐧌�
        velocity_.y += gravity_ * jumpDelta_;

        // �n�ʂɒ��n�����Ƃ�
        if (transform_.position_.y <= 0)
        {
            // �n�ʂɍ��킹��
            transform_.position_.y = 0;

            // ���n�����琂�����x�����Z�b�g
            velocity_.y = 0.0f;

            // �n�ʂɒ��n������W�����v�\�ɂ���
            canJump_ = true;
        }
    }
}