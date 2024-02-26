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
    // �v���C���[�̌����Ă������
    //float rotY = pPlayer_->GetRotate().y;

    // �G�l�~�[�̌����Ă������
    XMFLOAT3 charaFoword;
    charaFoword.x = (float)sin(XMConvertToRadians(transform_.rotate_.y));
    charaFoword.z = (float)cos(XMConvertToRadians(transform_.rotate_.y));

    // ���K��
    /////////////////////////����

    // �G�l�~�[�̎��E�p�x�i���p�j
    const float fovAngle = XMConvertToRadians(180.0f);

    // �v���C���[�����E���ɂ��邩�ǂ����𔻒�
    XMFLOAT3 toPlayer = CheckPlayerDirection();
    XMVECTOR vecToPlayer = XMLoadFloat3(&toPlayer);

    float dotProduct;
    XMStoreFloat(&dotProduct, XMVector3Dot(XMLoadFloat3(&transform_.rotate_), vecToPlayer));

    if (dotProduct >= cos(fovAngle / 2))
    {
        transform_.scale_.y = 0.2f;
        // �v���C���[�����E���ɂ���ꍇ�̏������L�q
        // �v���C���[�܂ł̋������v�Z
        float dist = CheckPlayerDistance();

        // �v���C���[�ʒu�܂ł̕����x�N�g�����v�Z
        XMFLOAT3 direction = CheckPlayerDirection();
        
        // �ړ����x�ɉ����Ĉړ��ʂ��v�Z
        XMFLOAT3 moveVector = { direction.x * status_.walkSpeed_, 0, direction.z * status_.walkSpeed_ };

        // �V�����ʒu���v�Z
        if (algorithm_.approachDistance_ <= dist)
        {
            transform_.position_ = CalculateFloat3Add(transform_.position_, moveVector);

            // �G�l�~�[���v���C���[�̕����Ɍ�����
            float newAngle = atan2(direction.z, direction.x);
            float angleDiff = newAngle - lastAngle_;
            if (angleDiff > XM_PI)
            {
                newAngle -= XM_2PI;
            }
            else if (angleDiff < -XM_PI)
            {
                newAngle += XM_2PI;
            }
            transform_.rotate_.y = -XMConvertToDegrees(newAngle);
            lastAngle_ = newAngle;

            OutputDebugString(std::to_string(dist).c_str());
            OutputDebugString("\n");
        }
    }
    else
        transform_.scale_.y = 1.0f;
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

