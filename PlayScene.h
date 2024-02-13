#pragma once
#include "Engine/GameObject.h"

class Player;
class EnemyManager;

//Playシーンを管理するクラス
class PlayScene : public GameObject
{
	int hPict_;    //画像番号
	EnemyManager* pEnemyManager_; // エネミーマネージャー
	Player* pPlayer_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;     //初期化
	void Update() override;         //更新
	void Draw() override;           //描画
	void Release() override;        //開放

	//タイマー
	void TimeProcess();
};