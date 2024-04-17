#pragma once
#include "Engine/GameObject.h"
#include <vector>

//Titleシーンを管理するクラス
class TitleScene : public GameObject
{
	// テキスト画像の内容
	enum 
	{
		TITLE = 0,
		START,
	};
	std::vector<int> hPict_;	// 画像番号

	Transform textTrans_;
	bool transFlag;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);
	~TitleScene();

	void Initialize() override;     //初期化
	void Update() override;         //更新
	void Draw() override;           //描画
	void Release() override;        //開放
};