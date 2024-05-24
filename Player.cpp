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
    : PlayerBase(parent, "Player"), pStateManager_(nullptr), pAim_(nullptr), pGauge_(nullptr)
{
    // �W���p�����[�^���Z�b�g
    commonParameter_.walkSpeed_ = GetPrivateProfileFloat("Parameter", "walkSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.runSpeed_ = GetPrivateProfileFloat("Parameter", "runSpeed", 0, "Settings/PlayerSettings.ini");
    commonParameter_.jumpVelocity_ = GetPrivateProfileFloat("Parameter", "jumpHeight", 0, "Settings/PlayerSettings.ini");

    // �X�e�[�^�X���Z�b�g
    commonStatus_.maxHp_ = GetPrivateProfileFloat("Status", "maxHp", 0, "Settings/PlayerSettings.ini");

    // �X�e�[�g�}�l�[�W���[
    pStateManager_ = new StateManager(this);

    // ���炩���ߏ�ԃC���X�^���X�𐶐����ēo�^
    pStateManager_->AddState("IdleState", new PlayerIdleState(pStateManager_));
    pStateManager_->AddState("WalkingState", new PlayerWalkingState(pStateManager_));
    pStateManager_->AddState("RunningState", new PlayerRunningState(pStateManager_));
    pStateManager_->AddState("JumpingState", new PlayerJumpingState(pStateManager_));

    // �������
    pStateManager_->ChangeState("IdleState");

    // �����蔻��t�^
    SphereCollider* pCollision = new SphereCollider(collisionOffset, collisionScale);
    AddCollider(pCollision);
}

// �f�X�g���N�^
Player::~Player()
{
    SAFE_DELETE(pStateManager_);

    // ���񂾂Ƃ��Ƀ|�C���^�[��null�ɂ���
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

    if (playerParams_.jumping_)
    {
        ApplyGravity();
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
        vMove = XMVector3Normalize(vMove);
        vMove *= speed;
        XMStoreFloat3(&playerParams_.movement_, vMove);
    }

    // �ړ��ɔ��f
    playerParams_.movement_.x += moveVector.x * playerParams_.acceleration_;
    playerParams_.movement_.z += moveVector.z * playerParams_.acceleration_;

    // �ړ��ʂ�K�p
    transform_.position_.x += playerParams_.movement_.x;
    transform_.position_.z += playerParams_.movement_.z;
}

// ������K�p����֐�
void Player::ApplyDeceleration()
{
    // �؋󒆂͌����W����ς���
    if (playerParams_.jumping_)
    {
        playerParams_.movement_.x *= playerParams_.friction_ * playerParams_.jumpFriction_;
        playerParams_.movement_.z *= playerParams_.friction_ * playerParams_.jumpFriction_;
    }
    else
    {
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
        // �m�b�N�o�b�N����
        EnemyBase* pEnemy = dynamic_cast<EnemyBase*>(pTarget);

        // HP���炷����
        DecreaseHp(pEnemy->GetEnemyStatus().attackPower_);
    }
}
