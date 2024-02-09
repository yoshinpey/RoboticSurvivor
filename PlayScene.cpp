#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "GameManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "PlayScene.h"
#include "Ground.h"
#include "Timer.h"
#include "Gauge.h"
#include "Score.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1), pEnemyManager_(nullptr), pPlayer_(nullptr)
{
}

//������
void PlayScene::Initialize()
{
	// �V�[���̓r���œo�ꂷ�郂�f���͐�ɓǂ�ł���
	Model::Load("DebugCollision/sphereCollider.fbx");
	Model::Load("Entity/Bullet.fbx");

	Instantiate<Ground>(this);			//�n�ʓo��
	
	//�G���o��������e�X�g
	pEnemyManager_ = new EnemyManager(this);
	pEnemyManager_->SpawnEnemy(XMFLOAT3(0, 2, 10), EnemyType::FLY);
	pEnemyManager_->SpawnEnemy(XMFLOAT3(10, 0, 10), EnemyType::GROUND);

	for (int i=1; i<=20; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 1, 10), EnemyType::FLY);
	}

	pEnemyManager_->SpawnEnemy(XMFLOAT3(0, 1, 10), EnemyType::EXPLOSION);

	//pEnemyManager_->RemoveEnemy(EnemyType::GROUND);

	pPlayer_ = (Player*)FindObject("Player");
	Instantiate<Player>(this);			//�v���C���[�o��

	//��UI�n���͑O�ʂɂȂ�悤�ɕ`��
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
	static float score = 0;	
	static int num = 0;
	num++;
	score = (num % 60) * 0.1f;

	s->ScoreAdd((int)score);

	// �f�o�b�O
	//�G�����ׂď�������Q�[���N���A
	if (FindObject("Enemy_Fly") == nullptr&& FindObject("Enemy_Ground") == nullptr)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
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
	SAFE_DELETE(pEnemyManager_);
	SAFE_DELETE(pPlayer_);
}

//�^�C�}�[
void PlayScene::TimeProcess()
{
#ifdef _DEBUG

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
#endif
}
