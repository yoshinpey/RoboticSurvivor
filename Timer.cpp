#include "Timer.h"
#include "Engine/Text.h"

namespace
{
    XMINT2 position = { 10,20 };
    int offsetX = 100;
    float defaultScale = 1.0f;
    int movingFlame = 10;
    float changeRate = 0.2f;
}

//�R���X�g���N�^
Timer::Timer(GameObject* parent)
    :GameObject(parent, "Timer"), pNum_(nullptr), frame_(0), active_(false)
{
    pNum_ = new Text;
}

//�f�X�g���N�^
Timer::~Timer()
{
}

//������
void Timer::Initialize()
{
    pNum_->Initialize();
}

//�X�V
void Timer::Update()
{
    // �N����Ԃ�����
    if (!active_) return;
    // �t���[���X�V
    if (frame_ > 0) --frame_;
}

//�`��
void Timer::Draw()
{
    // �e�L�X�g�̃T�C�Y
    pNum_->SetScale(defaultScale);
    pNum_->Draw(position.x, position.y, "Timer:");

    // �����̖��������o���B
    // �t���[�����������]�肪10�ȉ���������
    if ((int)frame_ % FPS < movingFlame)
        pNum_->SetScale(((int)frame_ % FPS) * changeRate + defaultScale);
    else 
        pNum_->SetScale(defaultScale);

    // �b��
    pNum_->Draw(position.x + offsetX, position.y, frame_ / FPS);
}

//�J��
void Timer::Release()
{
    pNum_->Release();
    SAFE_DELETE(pNum_)
}