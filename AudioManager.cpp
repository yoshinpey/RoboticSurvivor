#include "AudioManager.h"
#include "Engine/Audio.h"
#include <cassert>
#include <vector>

#include <fstream>
#include <string>
#include <sstream>

namespace AudioManager
{
    // サウンドハンドル
    std::vector<int> hSound_;

    // 音量(0.0f ～1.0f)
    float volue_ = 0.2f;  

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

void AudioManager::InitVolue()
{
    // ファイル読み込み
    std::ifstream ifs("Settings/AudioVolume.txt");
    std::string data;
    ifs >> data;

    // stringからintへ変換し、そのあと値をセット
    std::istringstream iss = std::istringstream(data);
    iss >> volue_;
    volue_ /= 100.0f;
}

void AudioManager::Play(AUDIO_ID id, float volume)
{
    Audio::Play(hSound_[id], volue_ * volume);
}

void AudioManager::Release()
{
    Audio::Release();
}