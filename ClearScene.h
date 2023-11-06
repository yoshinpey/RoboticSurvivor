#pragma once
#include "Engine/GameObject.h"

//Clearシーンを管理するクラス
class ClearScene : public GameObject
{
	int hPict_;    //画像番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ClearScene(GameObject* parent);

	void Initialize() override;     //初期化
	void Update() override;         //更新
	void Draw() override;           //描画
	void Release() override;        //開放
};