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
#include "SkyBox.h"

PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), pEnemyManager_(nullptr), pSceneManager_(nullptr)
{
	pEnemyManager_ = new EnemyManager(this);
	pSceneManager_ = (SceneManager*)FindObject("SceneManager");
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	// シーンの途中で登場するモデルは先に読んでおく
	Model::Load("DebugCollision/sphereCollider.fbx");
	Model::Load("Entity/Bullet.fbx");

	Instantiate<Ground>(this);			//地面登場

	pPlayer_=Instantiate<Player>(this);			//プレイヤー登場
	Instantiate<SkyBox>(this);			//プレイヤー登場

	////初回の敵を出現させるテスト
	for (int i=1; i<=20; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(0, 0, 15), EnemyType::FLY);
	}
	

	//※UI系統は前面になるように描画
	Instantiate<Timer>(this);			//タイマー登場
	Instantiate<Gauge>(this);			//HPゲージ	
	Instantiate<Score>(this);			//スコア表示

	//タイマー設定
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(5);
	t->Start();
}

void PlayScene::Update()
{

	////////////////////////デバック用
	// 敵の出現テスト 
	// プレイヤーの位置を使って相対座標で出現させる用の変数
	XMFLOAT3 plaPos = pPlayer_->GetPosition();

	// 指定した座標に指定した敵をスポーン
	if (Input::IsKeyDown(DIK_1))
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(plaPos.x, plaPos.y, plaPos.z + 5), EnemyType::FLY);
	}
	
	// 指定した座標に指定した敵を複数体スポーン
	if (Input::IsKeyDown(DIK_2))
	{
		pEnemyManager_->SpawnMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(0, 0, 5)),
			CalculateFloat3Add(plaPos, XMFLOAT3(0, 0, 10)),
			3, 
			EnemyType::FLY);
	}

	// 指定した座標にランダムな敵を出現させる。
	if (Input::IsKeyDown(DIK_3))
	{
		pEnemyManager_->SpawnRandomMultiEnemy(XMFLOAT3(-20, 0, 20), XMFLOAT3(-10, 0, 30), 2);
	}

	// 指定した座標にランダムな敵を出現させる。今回グラウンドを除外してる
	if (Input::IsKeyDown(DIK_4))
	{
		pEnemyManager_->SpawnRandomMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(10, 2, 10)),
			CalculateFloat3Add(plaPos, XMFLOAT3(20, 5, 20)),
			3,
			EnemyType::GROUND);
	}



	// 特定のエネミー消す
	if (Input::IsKeyDown(DIK_4))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::GROUND);
	}

	// 全部のエネミー消し炭
	if (Input::IsKeyDown(DIK_5))
	{
		pEnemyManager_->RemoveAllEnemies();
	}





	TimeProcess();	

	// タイム制ウェーブスポーンのテスト用
	Timer* t = (Timer*)FindObject("Timer");
	int time = t->GetFlame();
	if (time % 300 == 0)
	{
		for (int i = 1; i < 20; i+=4)
		{
			pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 0, 30), EnemyType::GROUND);
		}
	}

	// 時間切れ
	if (time == 0)
	{
		pEnemyManager_->RemoveAllEnemies();
		
		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}


	//////スコアテスト用
	Score* s = (Score*)FindObject("Score");
	static float score = 0;	
	static int num = 0;
	num++;
	score = (num % 60) * 0.1f;

	s->ScoreAdd((int)score);

	// デバッグ
	//敵がすべて消えたらゲームクリア
	if (FindObject("Enemy_Fly") == nullptr&& FindObject("Enemy_Ground") == nullptr && FindObject("Enemy_Explosion") == nullptr)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}
	////////////////////////
}

void PlayScene::Draw()
{
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
