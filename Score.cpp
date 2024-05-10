#include "Score.h"

namespace
{
    XMINT2 position = { 50,700 };
}

//�R���X�g���N�^
Score::Score(GameObject* parent) : GameObject(parent, "Score"), pText(nullptr), score_(0)
{
    pText = new Text;
}

//�f�X�g���N�^
Score::~Score()
{
}

//������
void Score::Initialize()
{
    pText->Initialize();
}

//�X�V
void Score::Update()
{
}

//�`��
void Score::Draw()
{
    //pText->Draw(position.x, position.y, score_);
}

//�J��
void Score::Release()
{
    pText->Release();
    SAFE_DELETE(pText)
}
