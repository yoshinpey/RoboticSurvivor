#pragma once
#include "Engine/GameObject.h"

class Player;
class Timer;
class EnemyManager;
class StageManager;
class SceneManager;

//Playシーンを管理するクラス
class PlayScene : public GameObject
{
	Player* pPlayer_;
	Timer* pTimer_;
	EnemyManager* pEnemyManager_;
	StageManager* pStageManager_;
	SceneManager* pSceneManager_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;     //初期化
	void Update() override;         //更新
	void Draw() override;           //描画
	void Release() override;        //開放

	void SetPlayer(Player* player) { pPlayer_ = player; }

	EnemyManager* GetEnemyManager() { return pEnemyManager_; }
	StageManager* GetStageManager() { return pStageManager_; }

	// シーンの切り替え判定関数
	void CheckAndChangeScene();
};