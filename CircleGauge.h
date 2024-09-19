#pragma once
#include "Engine/GameObject.h"
#include <string>

class KuruKuruImage;

class CircleGauge : public GameObject
{
	KuruKuruImage* kImage_;
	float startAngle_;
	float endAngle_;
	float def_startAngle_;//初期位置を保存
	float def_endAngle_;//初期位置を保存
	float lapTime_;
	float lapFrameTime_;
	bool  isActive_;
	bool isIncrease_;
	bool isGaugeFull_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CircleGauge(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetStartAngle(float start, bool isinc);
	void SetLapTime(float laptime);
	void Start();
	void Stop();
	void Reset();

	void LaodIage(std::string fileName);

	void CircleDraw();

	void SetGaugeFullStop(bool flag) { isGaugeFull_ = flag; };
};

