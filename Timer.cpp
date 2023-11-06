#include "Timer.h"
#include "Engine/Input.h"

//�t���[�����[�g
static const int FPS = 60;

//�R���X�g���N�^
Timer::Timer(GameObject* parent)
    :GameObject(parent, "Timer"), pNum(nullptr),
    Frame(0), Active(false), drawX(10), drawY(20)
{
}

//�f�X�g���N�^
Timer::~Timer()
{
}

//������
void Timer::Initialize()
{
    pNum = new Text;
    pNum->Initialize();
}

//�X�V
void Timer::Update()
{
    //�N�����
    if (Active) 
    {
        //�J�E���g�_�E��
        if (Frame > 0) 
        {
            Frame--;
        }
    }
}

//�`��
void Timer::Draw()
{
    
    pNum->SetScale(1.0f);                                   //�e�L�X�g�̃T�C�Y
    pNum->Draw(drawX, drawY, "Time:");                      //�`����e

    if (Frame % FPS < 10)                                   //�����̖�����
        pNum->SetScale((Frame % FPS) * 0.2f + 1.0f);        //�K��t���[���ȉ����ɓK��
    else
        pNum->SetScale(1.0f);

    int sec = Frame / FPS;                                  //�b��
    pNum->Draw(drawX + 100, drawY, sec);
}

//�J��
void Timer::Release()
{
}

//�^�C�}�[�ݒ�
void Timer::SetLimit(float seconds)
{
    Frame = (int)(seconds * FPS);
}

//�^�C�}�[�J�n
void Timer::Start()
{
    Active = true;
}

//�^�C�}�[�I��
void Timer::Stop()
{
    Active = false;
}

//�^�C�}�[�����I��
bool Timer::IsFinished()
{
    return (Frame == 0);
}
