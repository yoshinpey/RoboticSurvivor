#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Gun.h"
#include "Bullet.h"


//�R���X�g���N�^
Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), Bullet_speed(1)
{
}

//�f�X�g���N�^
Gun::~Gun()
{
}

//������
void Gun::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Entity/Rifle_re.fbx");
    assert(hModel_ >= 0);

    //�v���C���[�̎�̈ʒu�܂Œ���
    transform_.position_.y = -1.25;
    transform_.position_.x = 0.25;
    transform_.position_.z = 1.5;
}

//�X�V
void Gun::Update()
{
    //���C
    if (Input::IsMouseButtonDown(0))
    {
        //�e���f����[
        XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
        //�e���f�����{
        XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
        //�x�N�g���ɕϊ�
        XMVECTOR vTop = XMLoadFloat3(&GunTop);
        XMVECTOR vRoot = XMLoadFloat3(&GunRoot);
        //�e�g����(�����܂�)�Z�o
        XMVECTOR vMove = vTop - vRoot;
        //���K��
        vMove = XMVector3Normalize(vMove);
        //�e��
        vMove *= Bullet_speed;
        //���ɖ߂�
        XMFLOAT3 move;
        XMStoreFloat3(&move, vMove);

        //�e���Ă�      Gun->Player->PlayScene
        Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent() -> GetParent());
        //�e�̈ʒu
        pBullet->SetPosition(GunTop); // ��C��[
        pBullet->SetMove(move);
    }
}

//�`��
void Gun::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Gun::Release()
{
}