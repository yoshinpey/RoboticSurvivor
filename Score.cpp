#include "Score.h"

//�R���X�g���N�^
Score::Score(GameObject* parent)
    :GameObject(parent, "Score"), pText(nullptr), 
    drawX_(50), drawY_(700)
{
}

//�f�X�g���N�^
Score::~Score()
{
}

//������
void Score::Initialize()
{
    pText = new Text;
    pText->Initialize();
}

//�X�V
void Score::Update()
{
}

//�`��
void Score::Draw()
{
    pText->Draw(drawX_, drawY_, score_);
}

//�J��
void Score::Release()
{
    delete pText;
    pText = nullptr;
}

//�X�R�A�����Z����
void Score::ScoreAdd(int score)
{
    score_ += score;
}

//�X�R�A���擾����
int Score::GetScore()
{
    return score_;
}