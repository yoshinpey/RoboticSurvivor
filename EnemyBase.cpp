#include "EnemyBase.h"

// デフォルトコンストラクタ
EnemyBase::EnemyBase()
    : GameObject(), CharacterBase(), name_("DefaultName"), id_(0)
{
}

// 引数を持つコンストラクタ
EnemyBase::EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id)
    : GameObject(spawnPosition), CharacterBase(), name_(name), id_(id)
{
}

// デストラクタ
EnemyBase::~EnemyBase()
{
}

// 初期化
void EnemyBase::Initialize()
{
}

// 更新
void EnemyBase::Update()
{
}

// 描画
void EnemyBase::Draw()
{
}

// 開放
void EnemyBase::Release()
{
}

// エネミー固有の挙動
void EnemyBase::SpecialAttack()
{
}
