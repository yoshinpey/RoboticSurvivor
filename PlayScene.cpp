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


PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1), pEnemyManager_(nullptr)
{
	pEnemyManager_ = new EnemyManager(this);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	// シーンの途中で登場するモデルは先に読んでおく
	Model::Load("DebugCollision/sphereCollider.fbx",0, Direct3D::SHADER_TYPE::SHADER_UNLIT);
	Model::Load("Entity/Bullet.fbx");

	Instantiate<Ground>(this);			//地面登場

	Instantiate<Player>(this);			//プレイヤー登場

	//敵を出現させるテスト
	pEnemyManager_->SpawnEnemy(XMFLOAT3(10, 0, 10), EnemyType::GROUND);
	for (int i=1; i<=20; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 1, 10), EnemyType::FLY);
	}

	pEnemyManager_->SpawnEnemy(XMFLOAT3(0, 1, -5), EnemyType::EXPLOSION);

	//※UI系統は前面になるように描画
	Instantiate<Timer>(this);			//タイマー登場
	Instantiate<Gauge>(this);			//HPゲージ	
	Instantiate<Score>(this);			//スコア表示

	//背景画像データのロード
	hPict_ = Image::Load("Pictures/Earth.png");
	assert(hPict_ >= 0);

	//タイマー設定
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(15);
}

void PlayScene::Update()
{

	//デバック用
	if (Input::IsKeyDown(DIK_K))
	{
		//pEnemyManager_->RemoveAllEnemies();
		pEnemyManager_->RemoveEnemy(EnemyType::GROUND);
	}

	if (Input::IsKeyDown(DIK_L))
	{
		//pEnemyManager_->RemoveAllEnemies();
		pEnemyManager_->RemoveAllEnemies();
	}

	if (Input::IsKeyDown(DIK_M))
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(10, 0, 10), EnemyType::GROUND);
	}


	TimeProcess();	

	//////スコアテスト用
	Score* s = (Score*)FindObject("Score");
	static float score = 0;	
	static int num = 0;
	num++;
	score = (num % 60) * 0.1f;

	s->ScoreAdd((int)score);

	// デバッグ
	//敵がすべて消えたらゲームクリア
	if (FindObject("Enemy_Fly") == nullptr&& FindObject("Enemy_Ground") == nullptr)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
}

void PlayScene::Draw()
{
	//背景描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	/*ちょっと楽しいバグ
	//背景描画
	// 画像のサイズ取得
	XMFLOAT3 size = Image::GetTextureSize(hPict_);

	// ディスプレイサイズに合わせる
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	// 描画設定
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	*/
}

void PlayScene::Release()
{
	SAFE_DELETE(pEnemyManager_);
}

//タイマー
void PlayScene::TimeProcess()
{
#ifdef _DEBUG

	//タイマー起動
	if (Input::IsKeyDown(DIK_T))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->Start();
	}
	//タイマー一時停止
	if (Input::IsKeyDown(DIK_Y))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->Stop();
	}
#endif
}
