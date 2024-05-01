#include "AudioManager.h"
#include "Engine/Global.h"
#include "Engine/Audio.h"
#include <vector>

namespace AudioManager
{
    // サウンドを保管するハンドル
    std::vector<int> hSound_;

    // 音量(0.0f ～1.0f)
    float gameVolume_;

    // オーディオのデータ
    struct AudioData
    {
        std::string fileName;       // ファイル名
        bool isLoop;                // ループ再生するかどうか
        int maxPlayCount;           // 同時に鳴らす最大数
    };

    // オーディオリスト
    std::vector<AudioData> audioList_;

}

void AudioManager::Initialize()
{
    // オーディオのリスト(enumの順番に並べる)
    audioList_ = 
    {
        {"Sound/aaaaaaa.wav", false, 3},
    };

    // audioList_の数に合わせてハンドルのサイズを初期化
    hSound_.resize(audioList_.size());

    // データリスト読み込み
    for (int i = 0; i < audioList_.size(); ++i) 
    {
        hSound_[i] = Audio::Load(audioList_[i].fileName, audioList_[i].isLoop, audioList_[i].maxPlayCount);
        assert(hSound_[i] >= 0);
    }
}

void AudioManager::InitVolume()
{
    // 設定ファイルから音量を取得
    gameVolume_ = GetPrivateProfileFloat("Audio", "GameVolume", 0, "setup.ini");

    // ボリュームを0.0f ～ 1.0fの範囲にする
    gameVolume_ /= 100.0f;
}

void AudioManager::Play(AUDIO_ID id, float volume)
{
    Audio::Play(hSound_[id], gameVolume_ * volume);
}

void AudioManager::Release()
{
    Audio::Release();
}