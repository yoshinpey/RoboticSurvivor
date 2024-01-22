#include "Enemy_Ground.h"

Enemy_Ground::Enemy_Ground(const XMFLOAT3& spawnPosition)
    : EnemyBase(EnemyType::GROUND), hModel_(-1)
{
}

Enemy_Ground::~Enemy_Ground()
{
}

void Enemy_Ground::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Enemy_01.fbx");
    assert(hModel_ >= 0);
}

void Enemy_Ground::Update()
{
}

void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Ground::Release()
{
}