#pragma once
#include "Engine/GameObject.h"

//Clear�V�[�����Ǘ�����N���X
class ClearScene : public GameObject
{
	int hPict_;    //�摜�ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ClearScene(GameObject* parent);

	void Initialize() override;     //������
	void Update() override;         //�X�V
	void Draw() override;           //�`��
	void Release() override;        //�J��
};