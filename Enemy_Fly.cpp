#include "Enemy_Fly.h"
#include "JsonReader.h"

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pCollision_(nullptr)
{
    // �v���C���[�̃X�e�[�^�X��ݒ�
    //characterStatus_.SetCharacterStatus(MAX_HP, ATK);
    //characterStatus_.SetMovementParameters(JUMP_HEIGHT, WALK_SPEED, RUN_SPEED);

    // Json�t�@�C������X�e�[�^�X�ƃA���S���Y����ǂݍ���
    JsonReader reader("Assets/EnemySetings.json");
    if (reader.loadJsonData())
    {
        auto& data = reader.getData();
        auto& status = data["Enemy_Fly"]["status"];
        auto& algorithm = data["Enemy_Fly"]["algorithm"];

        // �X�e�[�^�X��ݒ�
        walkSpeed_ = status["walkSpeed"];
        attackPower_ = status["attackPower"];
        attackCooldown_ = status["attackCooldown"];

        // �A���S���Y����ݒ�
        detectPlayerDistance_ = algorithm["detectPlayerDistance"];
        patrolRadius_ = algorithm["patrolRadius"];
        approachDistance_ = algorithm["approachDistance"];
        attackDistance_ = algorithm["attackDistance"];
    }
}

Enemy_Fly::~Enemy_Fly()
{
}

void Enemy_Fly::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Enemy.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // �����蔻��t�^
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 1.5f);
    AddCollider(pCollision_);
}

void Enemy_Fly::Update()
{
    // �R���W�����̑傫�������f���ɍ��킹��
    // pCollision_->SetRadius(transform_.scale_.x);
}

void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Fly::Release()
{
}

void Enemy_Fly::OnCollision(GameObject* pTarget)
{
    /*
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Fly::Attack()
{
}
