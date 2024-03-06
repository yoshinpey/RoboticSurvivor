#pragma once
#include "Engine/GameObject.h"

class Player;
class EnemyManager;

//Play�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	EnemyManager* pEnemyManager_;
	SceneManager* pSceneManager_;
	Player* pPlayer_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;     //������
	void Update() override;         //�X�V
	void Draw() override;           //�`��
	void Release() override;        //�J��
};