#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "Aim.h"
#include "Player.h"
#include "Gauge.h"


//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr),
    gravity_(-1), canJump_(true), maxHp_(100), nowHp_(100), jumpVelocity_(JUMP_HEIGHT), jumpDelta_(0.08f), velocity_(0.0f, 0.0f, 0.0f),
    walkSpeed_(WALK_SPEED), runSpeed_(RUN_SPEED), isMoving_(false), movement_(0.0f, 0.0f, 0.0f), acceleration_(0.01f), friction_(0.8f)
{
    // �v���C���[�̃X�e�[�^�X��ݒ�
    characterStatus_.SetCharacterStatus(MAX_HP, ATK);
    characterStatus_.SetMovementParameters(JUMP_HEIGHT, WALK_SPEED, RUN_SPEED);
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
    stateManager_->Initialize();

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
    // �X�e�[�g�}�l�[�W���[�̍X�V
    stateManager_->Update();

    // �������Ă��Ȃ��Ƃ��A�X�e�[�g�}�l�[�W���[����Ԃ��A�C�h���ɕύX
    if (!InputManager::IsMoveForward() && !InputManager::IsMoveLeft() && !InputManager::IsMoveBackward() && !InputManager::IsMoveRight())
    {
        stateManager_->ChangeState(new IdleState(stateManager_));
        return;
    }

    // �ړ��L�[�������ꂽ��
    if (InputManager::IsMoveForward() || InputManager::IsMoveLeft() || InputManager::IsMoveBackward() || InputManager::IsMoveRight())
    {
        stateManager_->ChangeState(new WalkingState(stateManager_));
    }

    // �O�i���Ƀ_�b�V���L�[�������ꂽ��
    if (InputManager::IsMoveForward() && InputManager::IsRun())
    {
        stateManager_->ChangeState(new RunningState(stateManager_));
    }

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump())
    {
        stateManager_->ChangeState(new JumpingState(stateManager_));
    }

}

//�`��
void Player::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    if (testDRW)
    {
        pNum->Draw(100, 100, "aaaaaaaaaaaaaaaaa");
    }
    
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
}

//�v���C���[��HP
void Player::PlayerHitPoint()
{
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

// �v���C���[�̈ړ�
void Player::Move()
{
    // �ړ�����
    XMFLOAT3 fMove = CalculateMoveInput();

    // ���݂̑��x
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&movement_)));

    // �ō����x
    float maxMoveSpeed = 0.0f;

    // �ړ����͂���
    if (isMoving_)
    {
        // �����Ă��邩�ǂ���
        if (InputManager::IsRun())
        {
            maxMoveSpeed = runSpeed_;    // ���葬�x�ɐݒ�
        }
        else
        {
            maxMoveSpeed = walkSpeed_;   // �������x�ɐݒ�
        }

        // �ő呬�x�𒴂��Ă����琳�K���E�ő�l�̒l�ɂ���
        if (currentSpeed > maxMoveSpeed)
        {
            XMVECTOR vMove = XMLoadFloat3(&movement_);
            vMove = XMVector3Normalize(vMove);
            vMove *= maxMoveSpeed;
            XMStoreFloat3(&movement_, vMove);
        }

        // ���݂̑��x��ڕW�̑��x�ɋ߂Â���
        if (currentSpeed < maxMoveSpeed)
        {
            velocity_.x += acceleration_;
            velocity_.z += acceleration_;
        }
        else
        {
            velocity_.x = maxMoveSpeed;
            velocity_.z = maxMoveSpeed;
        }

        // �ړ��ɔ��f
        movement_.x += fMove.x * velocity_.x;
        movement_.z += fMove.z * velocity_.z;

        // �ړ��ʂ�K�p
        transform_.position_.x += movement_.x;
        transform_.position_.z += movement_.z;
    }
    else
    {
        // �e�ړ��{�^���𗣂����Ƃ��Ɍ�����K��
        movement_.x *= friction_;
        movement_.z *= friction_;
        velocity_.x = 0;
        velocity_.z = 0;

        // �ړ��ɔ��f
        transform_.position_.x += movement_.x;
        transform_.position_.z += movement_.z;
    }
}

void Player::Walk()
{
    // �ړ�����
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // �������x�ɐݒ�
    float walkSpeed = WALK_SPEED;

    // �ړ��x�N�g��
    XMFLOAT3 walkVector = XMFLOAT3(moveDirection.x * walkSpeed, 0.0f, moveDirection.z * walkSpeed);

    // �ړ��ɔ��f
    ApplyMovement(walkVector, walkSpeed);
}

void Player::Run()
{
    // �ړ�����
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // ���葬�x�ɐݒ�
    float runSpeed = RUN_SPEED;

    // �ړ��x�N�g��
    XMFLOAT3 runVector = XMFLOAT3(moveDirection.x * runSpeed, 0.0f, moveDirection.z * runSpeed);

    // �ړ��ɔ��f
    ApplyMovement(runVector, runSpeed);
}

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

    // ���݂̑��x��ڕW�̑��x�ɋ߂Â���
    if (currentSpeed < speed)
    {
        velocity_.x += acceleration_;
        velocity_.z += acceleration_;
    }
    else
    {
        velocity_.x = speed;
        velocity_.z = speed;
    }

    // �ړ��ɔ��f
    movement_.x += moveVector.x * velocity_.x;
    movement_.z += moveVector.z * velocity_.z;

    // ���C�ɂ�錸��
    movement_.x *= friction_;
    movement_.z *= friction_;

    // �ړ��ʂ�K�p
    transform_.position_.x += movement_.x;
    transform_.position_.z += movement_.z;
}

// �W�����v
void Player::Jump()
{
    // �؋�
    if (!canJump_)
    {
        // ������ւ̈ړ�����
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

// �ړ��v�Z���s���֐�
XMFLOAT3 Player::CalculateMoveInput()
{
    XMFLOAT3 fMove = XMFLOAT3(0.0f, 0.0f, 0.0f);

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

    // ���K��
    XMVECTOR vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    XMStoreFloat3(&fMove, vMove);

    return fMove;
}
