#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "Timer.h"
#include "Score.h"
#include "SkyBox.h"

#include "AudioManager.h"
#include "EffectManager.h"
#include "EnemyManager.h"

#include <array>

namespace
{
	// このシーンで使用するモデル群
	std::array<std::string, 6> modelName = 
	{
		"DebugCollision/sphereCollider.fbx",
		"Entity/Bullet.fbx",
		"Entity/Missile.fbx",
		"Enemy/Enemy_Ground.fbx",
		"Enemy/Enemy_Fly.fbx",
		"Enemy/Enemy_Explosion.fbx"
	};
	////////////WaveTest
	XMFLOAT3 spawnPosition;		// スポーンする位置
	int waveTimer = 300;		// 出現の区切り時間
}

PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), pEnemyManager_(nullptr), pSceneManager_(nullptr), pPlayer_(nullptr)
{
	pEnemyManager_ = new EnemyManager(this);
	pSceneManager_ = (SceneManager*)FindObject("SceneManager");
	/////////////////////////////////////////
	AudioManager::Initialize();
	EffectManager::Initialize();
	/////////////////////////////////////////
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	// シーンの途中で登場するモデルは先にロードだけしておく(ラグ対策)
	for (int i = 0; i < modelName.size(); ++i)
	{
		Model::Load(modelName[i]);
	}

	Instantiate<Stage>(this);			// 地面登場
	Instantiate<SkyBox>(this);			// 空登場
	pPlayer_=Instantiate<Player>(this);			//プレイヤー登場
	
	///////////////////初回の敵を出現させるテスト
	for (int i = -10; i < 10; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 0, 5), EnemyType::GROUND);
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
	//敵がすべて消えたらゲームクリア
	if (pEnemyManager_->GetEnemyCount() == 0)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}

	Timer* pTimer = static_cast<Timer*>(FindObject("Timer"));

	// 時間切れ
	if (pTimer->IsFinished() || pPlayer_ == nullptr)
	{
		pEnemyManager_->RemoveAllEnemies();
		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}

	////////////////////////敵の個体数デバッグログ
		static float count[4] = {0,0,0,0};
	count[0] = pEnemyManager_->GetEnemyCount(EnemyType::GROUND);
	count[1] = pEnemyManager_->GetEnemyCount(EnemyType::EXPLOSION);
	count[2] = pEnemyManager_->GetEnemyCount(EnemyType::FLY); 
	count[3] = pEnemyManager_->GetEnemyCount(); 
	std::string output = 
		"Ground		: " + std::to_string(count[0]) + "\n"
		"Explosion	: " + std::to_string(count[1]) + "\n"
		"Fly			: " + std::to_string(count[2]) + "\n"
		"All			: " + std::to_string(count[3]) + "\n";
	if(Input::IsKeyDown(DIK_TAB))
		OutputDebugStringA(output.c_str());

	////////////////////////デバック用

	// プレイヤーいるときだけ処理する
	if (!pPlayer_)return;

	// プレイヤーの位置を使って相対座標で出現させる用の変数
	XMFLOAT3 plaPos = pPlayer_->GetPosition();
	XMFLOAT3 plaDir = pPlayer_->CalculateMoveInput();
	//plaPos = CalculateFloat3Add(plaPos, plaDir);

	if (pTimer->GetFrame() % waveTimer * 3 == 0)
	{
		XMFLOAT3 minPos = XMFLOAT3(-5, 3, 5);
		XMFLOAT3 maxPos = XMFLOAT3(5, 6, 10);
		int count = 3;
		std::vector<EnemyType> enemyID = { EnemyType::EXPLOSION, EnemyType::FLY };

		// 指定した座標にランダムな敵を出現させる。今回爆発とフライから選ぶ
		pEnemyManager_->SpawnRandomMultiEnemy
		(
			CalculateFloat3Add(plaPos, minPos),
			CalculateFloat3Add(plaPos, maxPos),
			count,
			enemyID
		);
	}
	//////////////////////////////////////

	// 特定のエネミー消す
	if (Input::IsKeyDown(DIK_1))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::FLY);
	}
	if (Input::IsKeyDown(DIK_2))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::GROUND);
	}
	if (Input::IsKeyDown(DIK_3))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::EXPLOSION);
	}

	// 全部のエネミー消し炭
	if (Input::IsKeyDown(DIK_4))
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
}

void PlayScene::CheckAndChangeScene()
{
	// 敵がすべて消えたらゲームクリア
	if (pEnemyManager_->GetEnemyCount() == 0)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}

	Timer* pTimer = static_cast<Timer*>(FindObject("Timer"));

	// 時間切れ、あるいはプレイヤーの死亡
	if (pTimer->IsFinished() || pPlayer_ == nullptr)
	{
		pEnemyManager_->RemoveAllEnemies();
		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}
}