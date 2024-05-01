#pragma once

namespace AudioManager 
{
	// 音源のID
	enum AUDIO_ID
	{
		TITLE = 0,
		MAX
	};

	// 初期化
	void Initialize();

	// 外部ファイルから設定音量を読み込む
	void InitVolume();

	// 音の再生
	void Play(AUDIO_ID id, float volume = 1.0f);

	// 解放
	void Release();

};