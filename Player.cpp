#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"

/*
<���v�����Ă��邱�ƃ��X�g>

//player
�����蔻����̖Y��Ă�
---�R���C�_�[����B
���f������]���ĂȂ�
---���N���X(�r������H)�Ƃ�����Ă������ɃJ���������ق����������������
HP�Q�[�W�̎�������
---���܂��e�̃_���[�W����Ƃ��ł��ĂȂ������ł�낤
�W�F�b�g�p�b�N�̃R�[�h�������邩�璼��
---�㏸�̉����������B���R��������Ƃ��̋������Ȃ񂩕ρB���ƃQ�[�W���o��������
�ʏ�W�����v�ƃW�F�b�g�p�b�N�̊|�����킹
---���Ƃł��B
�����Ƒ���ɉ�����t����
---�F�X���������ǌ��\�ނ����C������
�ړ����͂���߂��Ƃ��s�^�b�Ǝ~�܂�̒���
---�������ł���Ύ����Ƃł��邩�Ȃ��Ďv���Ă�
�t�L�[����͂����犵���̖@�������������ɂ�����
---����
���Ⴊ�ݍ�肽��
---���f�������ւ��Ĕ���𔼕��ɂ��邾��
�X���C�f�B���O��肽��
---��͂�v���C���[�̓��Ƒ̂��ꏏ�ɂ����̂��ԈႢ��������Ȃ��E�E�E�E
---�J�������ǂ����邩���ۑ�B���̖ڐ��̂܂ܑ̂����ɂ��ăX���C�f�B���O�����炨���炭�o�O��
---�X���C�f�B���O���͌Œ�J�����ɂ����Ⴈ�����E�E�E�H���邢�̓N���X�𕪂���΂�������

//gun
�����蔻������C�L���X�g�ɂ��邩�A�������̓m�Y���̐�[����R���C�_�[��L�΂��Ĕ�������Ƃ���肽���B
���ُ̈�Ԃ��ƒe�����Ƃ����邵�A�{���FPS�v���C���[�Ȃ��p���s���B���e�X�s�[�h���x���̂��X�g���X

//bomb
���f���ǉ����Ď��Ԍo�߂œK���ɃT�E���h�ƃG�t�F�N�g�Đ����ăR���C�_�[�L����΂�������

//winmain
�X�N���[���̍��W�擾�ŃX�N���[���T�C�Y���f�B�X�v���C�T�C�Y�ɍ��킹����

//�e�V�[��
���ꂼ��摜�p�ӂ�����Ȃ񂩓��������肵����
---�^�C�}�[�Ƃ��X�R�A�̔��f�Ƃ����l���˂�

//enemy
�߂Â��Ĕ������Ă���G�����
---�o�H�T���̎����������悭�킩���ĂȂ�
---�ǂ�������Ƃ��O�ɒN������Ă���ȋ����Ăق���
---���̂Ɠ��ŕʂ̔���t���ă_���[�W�{���ς�����
����ŉ������U���𔄂��Ă���G�����
---�ʂ�����Ƃ����[�U�[�r�[��
---�����������������ׂ邩��A�v���C���[������̋����ۂ��čU�����ė���Ƃ���肽��
---�e�����Ƃ�����悤�ɂł�����Ɉ��߂��čō�

//�N���X�^��
�X�R�A�A�b�v�A�C�e���ɂ��邩�r�ŃX�L���ɂ��邩����

//
*/

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr),
    gravity_(-0.3), maxFuel_(50), fuel_(0), jumpCool_(0), CanJump_(false), jampVelocity_(1.0),
    maxHp_(100), nowHp_(100)
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
    Jump();               //�W�����v�A�N�V����
    //JetPack();              //�W�F�b�g�p�b�N
    //BoostJump();          //�u�[�X�g�W�����v
    CameraPosition();       //���_
    PlayerHitPoint();       //HP
}

//�`��
void Player::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�f�o�b�N�p�e�L�X�g
    pNum->Draw(50, 200, "fuel");
    pNum->Draw(50, 250, fuel_);
    pNum->Draw(50, 400, "jumpCool");
    pNum->Draw(50, 450, jumpCool_);

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

//���_
void Player::CameraPosition()
{
#if 0
    //�e�X�g�p�̃J����
    XMFLOAT3 camPos{ 0, 10, -20 };
    XMFLOAT3 camTag{ 0, 0, 0 };
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTag);
#endif
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
    if (Input::IsKey(DIK_W)) {
        fMove.x += aimDirection.x;
        fMove.z += aimDirection.z;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x -= aimDirection.z;
        fMove.z += aimDirection.x;
    }
    if (Input::IsKey(DIK_S)) {
        fMove.x -= aimDirection.x;
        fMove.z -= aimDirection.z;
    }
    if (Input::IsKey(DIK_D)) {
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
    float runSpeed = 0.4f;          // ���s���x
    float nowSpeed = 0;             // �������x

    // �ړ����͂����邩�ǂ���
    bool isMoving = Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D);

    // �ړ����͂���
    if (isMoving)
    {
        // �����Ă��邩�ǂ���
        if (Input::IsKey(DIK_LSHIFT))
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
    float velocity = 5.0f;              // �����x
    float delta = 0.02f;                // �K���Ȃ����������l
    float gravity = -9.81;               // 
    static bool canJump = true;         // �W�����v�\�ȏ�Ԃ��ǂ���
    static float flightTime = 0.0f;     // �W�����v�o�ߎ���

    if (Input::IsKeyDown(DIK_SPACE) && canJump) //�W�����v�L�[��������Ă���A�W�����v�\�ȏꍇ
    {
        flightTime = 0.0f;
        canJump = false;                // �A���W�����v��h�~���邽�߁A�W�����v���̓W�����v�t���O�𖳌���
    }

    if (!canJump)
    {
        //�W�����v���Ă���̎��Ԃ̌o��
        flightTime += delta;
        
        //���������グ�^��          y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * flightTime + 0.5f * gravity * flightTime * flightTime;
        transform_.position_.y = pos;

        //�d�͂ɂ�闎��
        velocity += gravity * delta;

        //�n�ʂɒ��n�����Ƃ�
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;     // �O�̂��ߒn�ʂɍ��킹��
            canJump = true;                 // �n�ʂɒ��n������W�����v�\�ɂ���
        }
    }
}

//�W�F�b�g�p�b�N
void Player::JetPack()
{
    float flightTime = 0.0f;    // �؋󒆂̎��Ԍo��
    float fallTime = 0.0f;      // ��������

    bool onGround = transform_.position_.y <= 0;    // �n�ʂɂ���Ƃ�
    bool hasFuel = fuel_ > 0;                       // �R��������Ƃ�

    // �d�͂͋󒆂ɂ���Ƃ��̂ݓ���
    if(!onGround) transform_.position_.y += gravity_ + fallTime;

    // �W�����v�\
    if(hasFuel)
    {
        if (Input::IsKey(DIK_SPACE)) // �W�����v�L�[���͂�����
        {
            if (flightTime <= 1) flightTime += 0.1;            //�������E�܂ŏ��X�ɉ���
            transform_.position_.y += jampVelocity_ + flightTime;  //���x�ɃW�����v���Ԃ�������
            fuel_--;                                            //�R�������炷
        }
        else
        {
            flightTime = 0; //�L�[���͂��Ȃ���Όo�ߎ���(����)�����Z�b�g
            fallTime += 0.2;
        }
    }

    // �n�ʂɂ��邩�R�����Ȃ�
    if (onGround && !hasFuel)
    {
        transform_.position_.y = 0.0f;
        if (jumpCool_ <= 0.0f) jumpCool_ += 20.0f;             // �킸���ȉ񕜑ҋ@���Ԃ�ݒ�
    }

    // �N�[���^�C����0�܂Ō��炷
    if (jumpCool_ > 0)   jumpCool_--;

    // �R���͒n�ʂɂ��ăN�[���^�C�����łȂ��Ƃ��ɉ�
    if (onGround && jumpCool_ <= 0)
    {
        if (fuel_ < maxFuel_) fuel_++; // �R�����ő�l�܂ŉ�
    }
}

//�g�ݍ��킹
void Player::BoostJump()
{
}
