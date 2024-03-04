#pragma once
#include "Engine/GameObject.h"
#include "Engine/Direct3D.h"

class TitleScene;

class Button : public GameObject
{
	int hPict_[2];
	int alpha_;				//�����x
	int frameAlpha_;		//�����x
	float width_;			//�{�^���̕�
	float height_;			//�{�^���̍���
	bool isButtonInactive_; //�{�^�����������m���Ȃ�
	bool isFirstPoint;		//����Ə���
	std::string name_;		//�{�^���ɕ\������Png��
	XMFLOAT3 widePos_;		//-1�`1����Ȃ�,-1280�`1280�Ƃ��̍��W
	XMFLOAT3 frameSize_;	//Frame�̃T�C�Y
	Direct3D::BLEND_MODE mode_;

public:
	Button(GameObject* parent);
	~Button();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//����:���Wx,y,�T�C�Yx.y, �摜�̖��O
	void SetValue(float x, float y, float w, float h, std::string n);
	//����:���Wx,y,�T�C�Yx.y, �摜�̖��O, �t���[���̖��O
	void SetValue(float x, float y, float w, float h, std::string n, std::string frame);

	void SetAlpha(int i) { alpha_ = i; }; //0�i�����j�`255�i�\���j
	void SetFrameAlpha(int i) { frameAlpha_ = i; }; //0�i�����j�`255�i�\���j
	void SetActive(bool b) { isButtonInactive_ = b; };
	bool IsWithinBound();
	std::string GetName() { return name_; };
	void SetBlendMode(int mode);

};