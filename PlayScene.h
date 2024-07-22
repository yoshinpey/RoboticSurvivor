#pragma once
#include "Engine/GameObject.h"
#include "SceneBase.h"
#include "EventManager.h"

class Player;
class Timer;
class EnemyManager;
class StageManager;
class SceneManager;

//Playシーンを管理するクラス
class PlayScene : public SceneBase, public IEventListener
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
	SceneManager* GetSceneManager() { return pSceneManager_; }

	// シーンの切り替え判定関数
	void CheckAndChangeScene();

	void OnEvent(const GameEvent& event) override
	{
		if (event.type == EVENT_TYPE_VICTORY)
		{
			// 勝利イベントの処理
			pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
		}
		else if (event.type == EVENT_TYPE_DEFEAT)
		{
			// 敗北イベントの処理
			pEnemyManager_->RemoveAllEnemies();
			pSceneManager_->ChangeScene(SCENE_ID_OVER);
		}
	}
};