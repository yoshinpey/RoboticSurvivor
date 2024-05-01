#pragma once

namespace AudioManager 
{
	// ������ID
	enum AUDIO_ID
	{
		TITLE = 0,
		MAX
	};

	// ������
	void Initialize();

	// �O���t�@�C������ǂݍ��ސݒ艹��
	void InitVolue();

	// ���̍Đ�
	void Play(AUDIO_ID id, float volume = 1.0f);

	// ���
	void Release();

};