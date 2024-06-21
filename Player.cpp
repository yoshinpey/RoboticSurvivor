#include "Player.h"
#include "StateManager.h"
#include "Aim.h"
#include "Gauge.h"
#include "PlayerState.h"
#include "EnemyBase.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 1.6f, 0.0f };    // �����蔻��̈ʒu
    float collisionScale = 0.6f;                        // �����蔻��̑傫��
}

// �R���X�g���N�^
Player::Player(GameObject* parent) 
    : Character(parent, "Player"), pStateManager_(nullptr), pAim_(nullptr), pGauge_(nullptr), knockDirection_(0.0f, 0.0f, 0.0f), isEnemyHit_(false)
{
    // �W���p�����[�^���Z�b�g
    commonParameter_.walkSpeed_ = GetPrivateProfileFloat("Parameter", "walkSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.runSpeed_ = GetPrivateProfileFloat("Parameter", "runSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.jumpVelocity_ = GetPrivateProfileFloat("Parameter", "jumpHeight", 0, "Settings/PlayerSettings.ini");
    commonParameter_.knockBackStrength_ = 0.1f;

    // �X�e�[�^�X���Z�b�g
    commonStatus_.maxHp_ = GetPrivateProfileFloat("Status", "maxHp", 0, "Settings/PlayerSettings.ini");

    // �X�e�[�g�}�l�[�W���[�ݒ�
    pStateManager_ = new StateManager(this);
    pStateManager_->AddState("IdleState", new PlayerIdleState(pStateManager_));
    pStateManager_->AddState("WalkingState", new PlayerWalkingState(pStateManager_));
    pStateManager_->AddState("RunningState", new PlayerRunningState(pStateManager_));
    pStateManager_->AddState("JumpingState", new PlayerJumpingState(pStateManager_));
    pStateManager_->ChangeState("IdleState");           // �������

    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionOffset, collisionScale);
    AddCollider(pCollision);
}

// �f�X�g���N�^
Player::~Player()
{
    SAFE_DELETE(pStateManager_);

    // ���񂾂Ƃ��Ƀv���C���[�̃|�C���^�[���������
    PlayScene* pPlayScene = static_cast<PlayScene*>(FindObject("PlayScene"));
    pPlayScene->SetPlayer(nullptr);
}

// ������
void Player::Initialize()
{
    // ���_�N���X�ǂݍ���
    pAim_ = Instantiate<Aim>(this);
    // HP�Q�[�W
    pGauge_ = Instantiate<Gauge>(this);
}

// �X�V
void Player::Update()
{
    // �X�e�[�g�}�l�[�W���[�̍X�V
    pStateManager_->Update();

    // HP�Q�[�W�Ăяo��
    pGauge_->SetHp(commonStatus_.maxHp_, commonStatus_.currentHp_);
    ///////////////////////// �f�o�b�O�p
    static float hp = 5.0f;
    if (Input::IsKeyDown(DIK_M))
    {
        IncreaseHp(hp);
    }
    if (Input::IsKeyDown(DIK_N))
    {
        DecreaseHp(hp);
    }
    //////////////////////////

    // �d�͉��Z
    ApplyGravity();
    
    // �G�ƏՓ�
    if (isEnemyHit_)
    {
        playerParams_.jumping_ = true;
        //// �����l�̒����Ńm�b�N�o�b�N�̈З͂�ύX���Ă���B////
        // �m�b�N�o�b�N����
        knockDirection_.x -= knockDirection_.x * commonParameter_.knockBackStrength_;
        knockDirection_.z -= knockDirection_.z * commonParameter_.knockBackStrength_;

        // Y���̃m�b�N�o�b�N�����Əd�͓K�p
        knockDirection_.y -= knockDirection_.y * (commonParameter_.knockBackStrength_ * 3.0f);

        transform_.position_.x += knockDirection_.x;
        transform_.position_.y += knockDirection_.y;
        transform_.position_.z += knockDirection_.z;

        // �m�b�N�o�b�N���قƂ�ǂȂ��Ȃ�����t���O�����Z�b�g
        if (fabs(knockDirection_.x) < 0.01f && fabs(knockDirection_.z) < 0.01 && fabs(knockDirection_.y) < 0.01f)
        {
            isEnemyHit_ = false;
        }
    }
}

// �`��
void Player::Draw()
{
}

// �J��
void Player::Release()
{
}

void Player::Walk()
{
    ApplyMovement(CalculateMoveInput(), commonParameter_.walkSpeed_);
}

void Player::Run()
{
    ApplyMovement(CalculateMoveInput(), commonParameter_.runSpeed_);
}

// �ړ��ɔ��f����֐�
void Player::ApplyMovement(const XMFLOAT3& moveVector, float speed)
{
    // ���݂̑��x
    float currentSpeed = XMVectorGetX(XMVector3Length(XMLoadFloat3(&playerParams_.movement_)));

    // �ő呬�x�𒴂��Ă����琳�K���A�ő�l�̒l�ɂ���
    if (currentSpeed > speed)
    {
        XMVECTOR vMove = XMLoadFloat3(&playerParams_.movement_);
        vMove = XMVector3Normalize(vMove) * speed;
        XMStoreFloat3(&playerParams_.movement_, vMove);
    }

    // �ړ��ɔ��f
    playerParams_.movement_.x += moveVector.x * playerParams_.acceleration_;
    playerParams_.movement_.z += moveVector.z * playerParams_.acceleration_;

    // �ړ��ʂ�K�p
    transform_.position_.x += playerParams_.movement_.x;
    transform_.position_.z += playerParams_.movement_.z;
}

// �ړ��̌�����K�p����֐�
void Player::ApplyDeceleration()
{
    // �����W����K������
    if (playerParams_.jumping_)
    {
        // �؋󒆂̌����W��
        playerParams_.movement_.x *= playerParams_.friction_ * playerParams_.jumpFriction_;
        playerParams_.movement_.z *= playerParams_.friction_ * playerParams_.jumpFriction_;
    }
    else
    {
        // �n�ʂɂ���Ƃ��̌����W��
        playerParams_.movement_.x *= playerParams_.friction_;
        playerParams_.movement_.z *= playerParams_.friction_;
    }

    // �ړ��ɔ��f
    transform_.position_.x += playerParams_.movement_.x;
    transform_.position_.z += playerParams_.movement_.z;
}

// �W�����v
void Player::Jump()
{
    if (playerParams_.jumping_) return;

    // �ړ��������擾
    XMFLOAT3 moveDirection = CalculateMoveInput();

    // �ړ��������W�����v�̕����Ƃ��ēK�p
    playerParams_.velocity_.x = commonParameter_.jumpVelocity_ * moveDirection.x;
    playerParams_.velocity_.y = commonParameter_.jumpVelocity_;
    playerParams_.velocity_.z = commonParameter_.jumpVelocity_ * moveDirection.z;

    // �W�����v�ł��Ȃ�����
    playerParams_.jumping_ = true;
}

// �ړ��v�Z���s���֐�
XMFLOAT3 Player::CalculateMoveInput()
{
    // �v�Z���ʓ����p
    XMFLOAT3 moveDirection = { 0.0f, 0.0f, 0.0f };

    // �t�L�[���͂�����ړ��ϐ��̋t�s����|���ăX�g�b�v������
    if (InputManager::IsMoveForward() && InputManager::IsMoveBackward() && !InputManager::IsMoveLeft() && !InputManager::IsMoveRight()) 
        return XMFLOAT3(-playerParams_.movement_.x, -playerParams_.movement_.y, -playerParams_.movement_.z);
    else if (InputManager::IsMoveLeft() && InputManager::IsMoveRight() && !InputManager::IsMoveForward() && !InputManager::IsMoveBackward()) 
        return XMFLOAT3(-playerParams_.movement_.x, -playerParams_.movement_.y, -playerParams_.movement_.z);
    else if (InputManager::IsMoveForward() && InputManager::IsMoveBackward() && !InputManager::IsMoveLeft() && !InputManager::IsMoveRight()) 
        return XMFLOAT3(-playerParams_.movement_.x, -playerParams_.movement_.y, -playerParams_.movement_.z);


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
    moveDirection = NormalizeFloat3(moveDirection);

    return moveDirection;
}

void Player::ApplyGravity()
{
    playerParams_.velocity_.y += playerParams_.gravity_ * playerParams_.jumpDelta_;
    transform_.position_.y += playerParams_.velocity_.y;


    //if (Input::IsKey(DIK_SPACE))transform_.position_.y += 0.6;
        
    // �n�ʂɓ��B������W�����v�\�ȏ�Ԃɖ߂�
    if (transform_.position_.y < 0)
    {
        transform_.position_.y = 0;
        playerParams_.jumping_ = false;
        playerParams_.velocity_.y = 0;
    }
}

// �����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    // �G�ɓ��������Ƃ�
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // �G�l�~�[�x�[�X�ɃL���X�g
        EnemyBase* pEnemy = dynamic_cast<EnemyBase*>(pTarget);

        // HP���炷����
        //if (!isEnemyHit_)DecreaseHp(pEnemy->GetEnemyStatus().attackPower_);
        // �J�����V�F�C�N���g���K�[
        pAim_->StartCameraShake(0.3f, 0.05f); // ����0.2, 0.5�b�Ԃ̃V�F�C�N

        // �G�ɂԂ�������m�b�N�o�b�N�l��ݒ肷��
        // �m�b�N�o�b�N�֐��Ɏ��g�̍��W�ƓG�̍��W�A�m�b�N�o�b�N������З͂�n��
        // �󂯎�������W�̈����Z�����āA���K�����s�����������߂�B
        // �����ɈЗ͂������ăm�b�N�o�b�N�x�N�g�����쐬����

        // �A�b�v�f�[�g�֐��Ō��ݒn�x�N�g���Ƀm�b�N�o�b�N�x�N�g���������Ă��m�b�N�o�b�N������B
        // ���������̂܂܂ł͂��܂ł��~�܂�Ȃ��̂ŁA�m�b�N�o�b�N�̌������s���B
        // �m�b�N�o�b�N�x�N�g����0���傫���Ȃ�����A�m�b�N�o�b�N�x�N�g���Ɍ����ϐ���������B
        // �����l���傫���قǌ��ʓI�Ƀm�b�N�o�b�N�̈З͂�������(�m�b�N�o�b�N�x�N�g����0�ɒB����܂ł̎��Ԃ����邽��)
        // Y���Ɋւ��Ă͂Ԃ���p�x���l��������ɔ�΂������̂ŁA1.0��^���A����Ɍ����l��n�{�����Ă��B
        // �m�b�N�o�b�N�x�N�g����0�ɂȂ�A���n�ʂɑ���������m�b�N�o�b�N�v�Z���I������B


        // �G�l�~�[�ʒu
        XMFLOAT3 enemyPos = pEnemy->GetPosition();

        // �v���C���[����G�l�~�[�ւ̕���(�m�b�N�o�b�N�̕���)�x�N�g�����v�Z
        knockDirection_ = CalculateDirection(transform_.position_, enemyPos);
        knockDirection_.y = 1.0f;   // 0���Ə�ɔ�΂Ȃ��̂�1�ɂ���
        isEnemyHit_ = true;
    }
}
