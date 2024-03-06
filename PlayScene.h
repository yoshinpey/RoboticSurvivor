#pragma once
#include "Engine/GameObject.h"

class Player;
class EnemyManager;

//Playシーンを管理するクラス
class PlayScene : public GameObject
{
	EnemyManager* pEnemyManager_;
	SceneManager* pSceneManager_;
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
};