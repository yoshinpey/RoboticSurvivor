#pragma once
#include "Engine/GameObject.h"
#include "EnemyManager.h"

//Play�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	int hPict_;    //�摜�ԍ�
	EnemyManager* enemyManager_; // �G�l�~�[�}�l�[�W���[
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	void Initialize() override;     //������
	void Update() override;         //�X�V
	void Draw() override;           //�`��
	void Release() override;        //�J��

	//�^�C�}�[
	void TimeProcess();
};