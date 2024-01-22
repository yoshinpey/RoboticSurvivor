#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

#include "PlayScene.h"
#include "Player.h"
#include "Ground.h"
#include "Timer.h"
#include "Gauge.h"
#include "Score.h"


//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Ground>(this);			//地面登場
	Instantiate<Player>(this);			//プレイヤー登場

	//※テキストは前面になるように描画
	Instantiate<Timer>(this);			//タイマー登場
	Instantiate<Gauge>(this);			//HPゲージ	
	Instantiate<Score>(this);			//スコア表示

	//背景画像データのロード
	hPict_ = Image::Load("Earth.png");
	assert(hPict_ >= 0);

	//タイマー設定
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(15);

	enemyManager_ = new EnemyManager(); // インスタンス生成
	enemyManager_->SpawnEnemy(XMFLOAT3(0, 0, 0), EnemyType::FLY);

}

//更新
void PlayScene::Update()
{
	TimeProcess();	

	//////スコアテスト用
	Score* s = (Score*)FindObject("Score");
	static int score = 0;	
	static int num = 0;
	num++;
	score = (num % 60) * 0.1f;

	s->ScoreAdd(score);
}

//描画
void PlayScene::Draw()
{
	//背景描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void PlayScene::Release()
{
	delete enemyManager_; // 解放
}

//タイマー
void PlayScene::TimeProcess()
{
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
}
