#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "Aim.h"
#include "Player.h"
#include "Gauge.h"

//�R���X�g���N�^
Player::Player(GameObject* parent) : CharacterBase(parent, "Player"),
    pNum(nullptr), stateManager_(nullptr), pAim_(nullptr),
    gravity_(-1), canJump_(true), maxHp_(100), nowHp_(100), jumpVelocity_(JUMP_HEIGHT), jumpDelta_(0.01f), velocity_(0.0f, 0.0f, 0.0f),
    walkSpeed_(WALK_SPEED), runSpeed_(RUN_SPEED), movement_(0.0f, 0.0f, 0.0f), acceleration_(0.01f), friction_(0.85f), jumpFriction_(1.15f),
    jumpDirection_(0.0f, 0.0f, 0.0f), jumpSpeed_(0.0f, 0.0f, 0.0f)
{
    // �v���C���[�̃X�e�[�^�X��ݒ�
    pCharacterBase_ = static_cast<Player*>(this);
    pCharacterBase_->SetCharacterStatus(maxHp_, nowHp_);
    pCharacterBase_->SetMovementParameters(jumpVelocity_, walkSpeed_, runSpeed_);
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    // �X�e�[�g�}�l�[�W���[�̏�����
    stateManager_ = new StateManager(this);
    stateManager_ -> Initialize();

    //�e�L�X�g
    pNum = new Text;
    pNum->Initialize();

    //���_�N���X�ǂݍ���
    InstantiateFront<Aim>(this);
    pAim_ = (Aim*)FindObject("Aim");
}

//�X�V
void Player::Update()
{
    // �X�e�[�g�}�l�[�W���[�̍X�V
    stateManager_->Update();

    // ��������
    if (!canJump_)
    {
        velocity_.y += gravity_ * jumpDelta_;
        transform_.position_.y += velocity_.y;

        // �n�ʂɓ��B������W�����v�\�ȏ�Ԃɖ߂�
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;
            canJump_ = true;

            velocity_.y = 0;
        }
    }
}

//�`��
void Player::Draw()
{

    //�f�o�b�N�p
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
    SAFE_DELETE(pNum);
}

//�v���C���[��HP
void Player::PlayerHitPoint()
{
    //////////////////UI�}�l�[�W���[�o�R�ɕύX�\��B
    //HP�Q�[�W�Ăяo��
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(maxHp_, nowHp_);

    //�f�o�b�O�p
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

void Player::Walk()
{
    // �ړ�����
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // �ړ��x�N�g��
    XMFLOAT3 walkVector = XMFLOAT3(moveDirection.x * walkSpeed_, 0.0f, moveDirection.z * walkSpeed_);

    // �ړ��ɔ��f
    ApplyMovement(walkVector, walkSpeed_);
}

void Player::Run()
{
    // �ړ�����
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // �ړ��x�N�g��
    XMFLOAT3 runVector = XMFLOAT3(moveDirection.x * runSpeed_, 0.0f, moveDirection.z * runSpeed_);

    // �ړ��ɔ��f
    ApplyMovement(runVector, runSpeed_);
}

// �ړ��ɔ��f����֐�
void Player::ApplyMovement(const XMFLOAT3& moveVector, float speed)
{
    // ���݂̑��x
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&movement_)));

    // �ő呬�x�𒴂��Ă����琳�K���E�ő�l�̒l�ɂ���
    if (currentSpeed > speed)
    {
        XMVECTOR vMove = XMLoadFloat3(&movement_);
        vMove = XMVector3Normalize(vMove);
        vMove *= speed;
        XMStoreFloat3(&movement_, vMove);
    }
    else
    {
        velocity_.x += acceleration_;
        velocity_.z += acceleration_;
    }

    // �ړ��ɔ��f
    movement_.x += moveVector.x * velocity_.x;
    movement_.z += moveVector.z * velocity_.z;

    // �ړ��ʂ�K�p
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;
}

// ������K�p����֐�
void Player::ApplyDeceleration()
{
    // �e�ړ��{�^���𗣂����Ƃ��Ɍ�����K��
    // �؋󒆂͌����W����ς���
    if (!canJump_)
    {
        movement_.x *= friction_ * jumpFriction_;
        movement_.z *= friction_ * jumpFriction_;
    }
    else
    {
        movement_.x *= friction_;
        movement_.z *= friction_;
    }
    velocity_.x = 0;
    velocity_.z = 0;

    // �ړ��ɔ��f
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;
}

// �W�����v
void Player::Jump()
{
    // �W�����v���͏d�͂�K�p���Ȃ�
    if (!canJump_) return;

    // �ړ��������擾
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // ���݂̑��x��ێ�
    XMFLOAT3 currentVelocity = velocity_;

    // �ړ��������W�����v�̕����Ƃ��ēK�p
    velocity_.x = jumpVelocity_ * moveDirection.x;
    velocity_.y = jumpVelocity_;
    velocity_.z = jumpVelocity_ * moveDirection.z;

    // �W�����v�\�ȏ�Ԃ𖳌��ɂ���
    canJump_ = false;

    // �ړ������Ƒ��x��ێ�
    jumpDirection_ = moveDirection;
    jumpSpeed_ = currentVelocity;
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