
#pragma once
#include "Engine/GameObject.h"

//Title�V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	int hPict_[2];    //�摜�ԍ�
	Transform textTrans_;
	bool transFlag;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);
	~TitleScene();

	void Initialize() override;     //������
	void Update() override;         //�X�V
	void Draw() override;           //�`��
	void Release() override;        //�J��
};