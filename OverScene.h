#pragma once
#include "Engine/GameObject.h"

//Overシーンを管理するクラス
class OverScene : public GameObject
{
	int hPict_;    //画像番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	OverScene(GameObject* parent);

	void Initialize() override;     //初期化
	void Update() override;         //更新
	void Draw() override;           //描画
	void Release() override;        //開放
};