#include "CircleGauge.h"
#include "KuruKuruImage.h"

namespace {
	float startAngle = 270.0f;
}

CircleGauge::CircleGauge(GameObject* parent)
	:GameObject(parent, "CircleGauge"),
	startAngle_(0), endAngle_(0), kImage_(nullptr), lapTime_(0)
{
}

void CircleGauge::Initialize()
{
	//シェーダーのdig = の360を270に変えて
	startAngle_ = 0.0f;
	endAngle_ = 360.0;
	kImage_ = new KuruKuruImage();
	kImage_->Load("IMG/Missile_Charging.png");
	lapTime_ = 60; //秒で指定？ デフォルトは６０ｓ
	lapFrameTime_ = 360.0f / (lapTime_ * 60);
	def_startAngle_ = startAngle_; //リセット用に初期位置を保存
	def_endAngle_ = endAngle_;		//リセット用に初期位置を保存
	isIncrease_ = true;
	isActive_ = false;
}

void CircleGauge::Update()
{
	if (isActive_)
	{
		//start,endは０～３６０で入力
		endAngle_ = endAngle_ - lapFrameTime_;
		if (endAngle_ < 0)
			endAngle_ = 360.0f;
	}
}

void CircleGauge::Draw()
{
	XMFLOAT3 isize = kImage_->GetTextureSize();
	transform_.Calclation();
	if (isIncrease_)
		kImage_->Draw(transform_, RECT{ 0, 0, (int)isize.x, (int)isize.y }, 1.0, startAngle_, endAngle_, startAngle);
	else
		kImage_->Draw(transform_, RECT{ 0, 0, (int)isize.x, (int)isize.y }, 1.0, endAngle_, startAngle_, startAngle);
}

void CircleGauge::Release()
{
	delete kImage_;
}


void CircleGauge::SetStartAngle(float start, bool isinc)
{
	startAngle_ = start;
	endAngle_ = start;
	def_startAngle_ = startAngle_; //リセット用に初期位置を保存
	def_endAngle_ = endAngle_;		//リセット用に初期位置を保存
	isIncrease_ = isinc;
}

void CircleGauge::SetLapTime(float laptime)
{
	lapTime_ = laptime; //秒で指定？
	lapFrameTime_ = 360.0f / (lapTime_ * 60);
}

void CircleGauge::Start()
{
	isActive_ = true;
}

void CircleGauge::Stop()
{
	isActive_ = false;
}

void CircleGauge::Reset()
{
	isActive_ = false;
	startAngle_ = def_startAngle_;
	endAngle_ = def_endAngle_;
}
