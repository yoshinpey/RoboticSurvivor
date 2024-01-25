#include "Enemy_Fly.h"
#include "EnemyManager.h"

//�R���X�g���N�^
Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY), hModel_(-1)
{
    // �v���C���[�̃X�e�[�^�X��ݒ�
    //characterStatus_.SetCharacterStatus(MAX_HP, ATK);
    //characterStatus_.SetMovementParameters(JUMP_HEIGHT, WALK_SPEED, RUN_SPEED);

}

//�f�X�g���N�^
Enemy_Fly::~Enemy_Fly()
{
}

//������
void Enemy_Fly::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Enemy.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    EnemyManager* pEnemyMganager_ = new EnemyManager(this);
    XMFLOAT3 pos = pEnemyMganager_->GetSpawnPosition_();
    transform_.position_ = pos;
}

//�X�V
void Enemy_Fly::Update()
{
}

//�`��
void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Enemy_Fly::Release()
{
}