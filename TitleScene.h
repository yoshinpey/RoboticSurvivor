#pragma once
#include "Engine/GameObject.h"
#include <vector>

// Title�V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	// �e�L�X�g�摜�̓��e
	enum 
	{
		TITLE = 0,
		START,
	};
	std::vector<int> hPict_;    // �摜�ԍ�

	Transform textTrans_;
	float time_;				// �T�C���J�[�u�̂��߂̎��ԕϐ�

public:
	// �R���X�g���N�^
	// �����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);
	~TitleScene();

	void Initialize() override;     // ������
	void Update() override;         // �X�V
	void Draw() override;           // �`��
	void Release() override;        // �J��
};
