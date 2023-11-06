#include "Engine/Model.h"

#include "Bomb.h"


//�R���X�g���N�^
Bomb::Bomb(GameObject* parent)
    :GameObject(parent, "Bomb"), hModel_(-1)
{
}

//�f�X�g���N�^
Bomb::~Bomb()
{
}

//������
void Bomb::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);
}

//�X�V
void Bomb::Update()
{
}

//�`��
void Bomb::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Bomb::Release()
{
}