#include "EnemyBase.h"

// �f�t�H���g�R���X�g���N�^
EnemyBase::EnemyBase()
    : GameObject(), CharacterBase(), name_("DefaultName"), id_(0)
{
}

// ���������R���X�g���N�^
EnemyBase::EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id)
    : GameObject(spawnPosition), CharacterBase(), name_(name), id_(id)
{
}

// �f�X�g���N�^
EnemyBase::~EnemyBase()
{
}

// ������
void EnemyBase::Initialize()
{
}

// �X�V
void EnemyBase::Update()
{
}

// �`��
void EnemyBase::Draw()
{
}

// �J��
void EnemyBase::Release()
{
}

// �G�l�~�[�ŗL�̋���
void EnemyBase::SpecialAttack()
{
}
