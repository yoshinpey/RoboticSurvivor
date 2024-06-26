#pragma once

// 音源のID
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
	// 初期化
	void Initialize();

	// 外部ファイルから設定音量を読み込む
	void InitVolume();

	// 設定音量の変更を外部ファイルに反映する
	// 引数：音量(0.0f ～ 1.0f)
	void SetVolume(float volume);

	// 音の再生
	// 引数：オーディオID, 音量(0.0f ～ 1.0f)
	void Play(AUDIO_ID id, float volume = 1.0f);

	// 音の停止
	// 引数：オーディオID
	void Stop(AUDIO_ID id);

	// 解放
	void Release();

};