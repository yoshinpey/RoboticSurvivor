#pragma once

// ������ID
enum AUDIO_ID
{
	EXPLODE = 0,
	SHOT,
	SHOT_EXPLODE,
	CURSOR_POINT,
	CURSOR_ENTER,
	MAX
};

namespace AudioManager
{
	// ������
	void Initialize();

	// �O���t�@�C������ݒ艹�ʂ�ǂݍ���
	void InitVolume();

	// �ݒ艹�ʂ̕ύX���O���t�@�C���ɔ��f����
	// �����F����(0.0f �` 1.0f)
	void SetVolume(float volume);

	// ���̍Đ�
	// �����F�I�[�f�B�IID, ����(0.0f �` 1.0f)
	void Play(AUDIO_ID id, float volume = 1.0f);

	// ���̒�~
	// �����F�I�[�f�B�IID
	void Stop(AUDIO_ID id);

	// ���
	void Release();

};