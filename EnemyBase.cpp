#include "EnemyBase.h"

// �f�t�H���g�R���X�g���N�^
EnemyBase::EnemyBase()
    : GameObject(), CharacterBase(), name_("DefaultName"), id_(0)
{
}

// ���������R���X�g���N�^
EnemyBase::EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id)
    : GameObject(), CharacterBase(), name_(name), id_(id)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()
{
}

void EnemyBase::Release()
{
}

void EnemyBase::SpecialAttack()
{
}
