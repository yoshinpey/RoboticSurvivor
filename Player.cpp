#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "InputManager.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"


//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr),
    gravity_(-9.8), canJump_(false), maxHp_(100), nowHp_(100), jumpVelocity_(5.0f), jumpDelta_(0.02f)
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

//�v���C���[�̈ړ�
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
    if (moveLength != 0)
    {
        fMove.x /= moveLength;
        fMove.z /= moveLength;
    }

    // ���x�̐���
    float walkSpeed = 0.2f;         // ���s���x
    float runSpeed = 0.3f;          // ���s���x
    float nowSpeed = 0;             // �������x

    // �ړ����͂����邩�ǂ���
    bool isMoving = InputManager::IsMoveForward() || InputManager::IsMoveLeft() || InputManager::IsMoveBackward() || InputManager::IsMoveRight();

    // �ړ����͂���
    if (isMoving)
    {
        // �����Ă��邩�ǂ���
        if (InputManager::IsRun())
        {
            nowSpeed = runSpeed;    // ���葬�x��ݒ�
        }
        else
        {
            nowSpeed = walkSpeed;   // �������x��ݒ�
        }
    }
    else
    {
        // �e�ړ��{�^���𗣂����Ƃ��ɑ��x�����Z�b�g
        nowSpeed = 0.0f;
    }

    // �ړ��ɔ��f
    transform_.position_.x += fMove.x * nowSpeed;
    transform_.position_.z += fMove.z * nowSpeed;
}

//�ʏ�W�����v
void Player::Jump()
{

    if (InputManager::IsJump() && canJump_) //�W�����v�L�[��������Ă���A�W�����v�\�ȏꍇ
    {
        flightTime_ = 0.0f;
        canJump_ = false;                // �A���W�����v��h�~���邽�߁A�W�����v���̓W�����v�t���O�𖳌���
    }

    if (!canJump_)
    {
        //�W�����v���Ă���̎��Ԃ̌o��
        flightTime_ += jumpDelta_;
        
        //���������グ�^��          y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = jumpVelocity_ * flightTime_ + 0.5f * gravity_ * flightTime_ * flightTime_;
        transform_.position_.y = pos;

        //�d�͂ɂ�闎��
        jumpVelocity_ += gravity_ * jumpDelta_;

        //�n�ʂɒ��n�����Ƃ�
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;     // �n�ʂɍ��킹��
            canJump_ = true;                 // �n�ʂɒ��n������W�����v�\�ɂ���
        }
    }
}