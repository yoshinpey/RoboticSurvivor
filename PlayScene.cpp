#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

#include "PlayScene.h"
#include "GameManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Ground.h"
#include "Timer.h"
#include "Score.h"
#include "SkyBox.h"
#include "Engine/Model.h"

namespace
{
	// modelLoad
	std::vector<std::string> modelName =
	{
		"DebugCollision / sphereCollider.fbx",
		"Entity/Bullet.fbx"
	};
	////////////WaveTest
	XMFLOAT3 spawnPosition; // スポーンする位置

	// 出現の区切り時間
	int waveTimer = 300;
}

PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), pEnemyManager_(nullptr), pSceneManager_(nullptr), pPlayer_(nullptr)
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
	for (int i = 0; i < modelName.size(); ++i)
	{
		Model::Load(modelName[i]);
	}

	Instantiate<Ground>(this);			// 地面登場
	Instantiate<SkyBox>(this);			// 空登場
	pPlayer_=Instantiate<Player>(this);			//プレイヤー登場
	
	////初回の敵を出現させるテスト
	for (int i=1; i<=20; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 5, 15), EnemyType::FLY);
	}

	//※UI系統は前面になるように描画
	Instantiate<Timer>(this);			//タイマー登場
	Instantiate<Score>(this);			//スコア表示

	//タイマー設定
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(30);
	t->Start();
}

void PlayScene::Update()
{
	////////////////////////デバック用
	// タイム制ウェーブスポーンのテスト用
	Timer* pTimer = static_cast<Timer*>(FindObject("Timer"));
	int time = pTimer->GetFrame();
	// プレイヤーの位置を使って相対座標で出現させる用の変数
	XMFLOAT3 plaPos = pPlayer_->GetPosition();
	//XMFLOAT3 plaDir = pPlayer_->CalculateMoveInput();

	if (time % waveTimer == 0)
	{
		// ウェーブの開始時間になったら敵をスポーンさせる
		// 指定した座標に指定した敵を複数体スポーン
		pEnemyManager_->SpawnMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(-5, 3, 5)),
			CalculateFloat3Add(plaPos, XMFLOAT3(5, 6, 10)),
			3,
			EnemyType::FLY
		);
	}
	
	if (time % waveTimer * 2 == 0)
	{

		// 指定した座標に指定した敵をスポーン
		pEnemyManager_->SpawnEnemy(XMFLOAT3(plaPos.x, plaPos.y+3, plaPos.z + 5), EnemyType::FLY);
	}

	if (time % waveTimer * 0.5 == 0)
	{
		// 指定した座標にランダムな敵を出現させる。
		pEnemyManager_->SpawnRandomMultiEnemy(XMFLOAT3(-20, 3, 20), XMFLOAT3(-10, 5, 30), 2);
	}

	if (time % waveTimer * 3 == 0)
	{
		// 指定した座標にランダムな敵を出現させる。今回フライを除外してる
		pEnemyManager_->SpawnRandomMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(10, 2, 10)),
			CalculateFloat3Add(plaPos, XMFLOAT3(20, 5, 20)),
			3
		);
	}

	//敵がすべて消えたらゲームクリア
	if (FindObject("Enemy_Fly") == nullptr && FindObject("Enemy_Ground") == nullptr && FindObject("Enemy_Explosion") == nullptr)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}
	// 時間切れ
	if (time == 0)
	{
		pEnemyManager_->RemoveAllEnemies();

		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}
	//////////////////////////////////////

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


	//////スコアテスト用
	//Score* s = (Score*)FindObject("Score");
	//static float score = 0;	
	//static int num = 0;
	//num++;
	//score = (num % 60) * 0.1f;

	//s->ScoreAdd((int)score);
	////////////////////////
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
	SAFE_DELETE(pEnemyManager_);
}