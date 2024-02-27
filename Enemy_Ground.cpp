#include "Enemy_Ground.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr), lastAngle_(0)
{
    // INI�t�@�C������f�[�^���\���̂֗�������
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Ground", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Ground", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Ground", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Ground", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Ground::~Enemy_Ground()
{
}

void Enemy_Ground::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Enemy_02.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // �����蔻��t�^
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 2.0f);
    AddCollider(pCollision_);

}

void Enemy_Ground::Update()
{
    // �v���C���[�ւ̕����x�N�g��(���K����)
    XMFLOAT3 direction = CheckPlayerDirection();

    // �v���C���[�����E���ɂ��邩�ǂ���
    if (IsPlayerInFieldOfView())
    {
        // �v���C���[�܂ł̋���
        float dist = CheckPlayerDistance();
        //OutputDebugString(std::to_string(dist).c_str());
        //OutputDebugString("\n");
    }

    // �f�o�b�O�p�A����p�ɓ����Ă邩�m�F���邽�߂̕ό`
    transform_.scale_.y = IsPlayerInFieldOfView() ? 0.2f : 1.0f;
}

bool Enemy_Ground::IsPlayerInFieldOfView()
{
    const float fieldOfView = XMConvertToRadians(20.0f); // ���E�p�x�����W�A���ɕϊ�
    XMFLOAT3 enemyForward = CheckPlayerDirection();

    // �v���C���[�ւ̕����x�N�g��(���K����)
    XMFLOAT3 toPlayer = CheckPlayerDirection();

    // ���E�̕����x�N�g�����v���C���[�ւ̕����x�N�g���Ɍ����ď��X�ɉ�]������
    float angle = acos(XMVectorGetX(XMVector3Dot(XMLoadFloat3(&enemyForward), XMLoadFloat3(&toPlayer)))); // �G�ƃv���C���[�̕����x�N�g���̓��ς���p�x�����߂�
    float rotateSpeed = XMConvertToRadians(1.0f); // ���E�̉�]���x�i1�x����]�j

    if (angle > rotateSpeed)
    {
        // ���E�̕����x�N�g�������X�Ƀv���C���[�ւ̕����x�N�g���Ɍ�����
        XMFLOAT3 newEnemyForward;
        XMStoreFloat3(&newEnemyForward, XMVector3Normalize(XMLoadFloat3(&enemyForward) + XMLoadFloat3(&toPlayer) * rotateSpeed));
        enemyForward = newEnemyForward;
    }
    else
    {
        // ���E�̕����x�N�g�����قڃv���C���[�ւ̕����x�N�g���ƈ�v����ꍇ�A���S�Ɉ�v������
        enemyForward = toPlayer;
    }

    // ���E�̕����x�N�g���ƃv���C���[�ւ̕����x�N�g���̊p�x�����E�p�x�̔����ȉ��ł���΃v���C���[�����E���ɂ���Ɣ���
    angle = acos(XMVectorGetX(XMVector3Dot(XMLoadFloat3(&enemyForward), XMLoadFloat3(&toPlayer)))); // �X�V�������E�̕����x�N�g���ƃv���C���[�ւ̕����x�N�g���̓��ς���p�x���Čv�Z

    // ���E�̕������X�V
    transform_.rotate_.y = atan2(enemyForward.x, enemyForward.z);

    return angle <= fieldOfView / 2;
}

void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{
    /*
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Ground::Attack()
{
}

