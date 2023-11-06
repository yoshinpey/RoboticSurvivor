#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

#include "Enemy_Fly.h"
#include "PlayScene.h"
#include "Player.h"
#include "Ground.h"
#include "Timer.h"
#include "Gauge.h"
#include "Score.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Ground>(this);			//�n�ʓo��
	Instantiate<Enemy_Fly>(this);		//�G�o��
	Instantiate<Player>(this);			//�v���C���[�o��

	//���e�L�X�g�͑O�ʂɂȂ�悤�ɕ`��
	Instantiate<Timer>(this);			//�^�C�}�[�o��
	Instantiate<Gauge>(this);			//HP�Q�[�W	
	Instantiate<Score>(this);			//�X�R�A�\��

	//�w�i�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Earth.png");
	assert(hPict_ >= 0);

	//�^�C�}�[�ݒ�
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(15);





}

//�X�V
void PlayScene::Update()
{
	TimeProcess();	

	//////�X�R�A�e�X�g�p
	Score* s = (Score*)FindObject("Score");
	static int score = 0;	
	static int num = 0;
	num++;
	score = (num % 60) * 0.1;

	s->ScoreAdd(score);
}

//�`��
void PlayScene::Draw()
{
	//�w�i�`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void PlayScene::Release()
{
}

//�^�C�}�[
void PlayScene::TimeProcess()
{
	//�^�C�}�[�N��
	if (Input::IsKeyDown(DIK_T))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->Start();
	}
	//�^�C�}�[�ꎞ��~
	if (Input::IsKeyDown(DIK_Y))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->Stop();
	}
}
