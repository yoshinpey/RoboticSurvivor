#pragma once
#include "Engine/GameObject.h"

class Player;
class Timer;
class EnemyManager;
class StageManager;
class SceneManager;

//Play�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	Player* pPlayer_;
	Timer* pTimer_;
	EnemyManager* pEnemyManager_;
	StageManager* pStageManager_;
	SceneManager* pSceneManager_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;     //������
	void Update() override;         //�X�V
	void Draw() override;           //�`��
	void Release() override;        //�J��

	void SetPlayer(Player* player) { pPlayer_ = player; }

	EnemyManager* GetEnemyManager() { return pEnemyManager_; }
	StageManager* GetStageManager() { return pStageManager_; }

	// �V�[���̐؂�ւ�����֐�
	void CheckAndChangeScene();
};