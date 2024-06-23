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
        {"Sounds/Explode.wav", false, 3},
        {"Sounds/Shot.wav", false, 3},
        {"Sounds/ShotExplode.wav", false, 3}
    };

    // リストの数に合わせてハンドルのサイズを初期化
    hSound_.resize(audioList_.size());

    // データリスト読み込み
    for (int i = 0; i < audioList_.size(); ++i) 
    {
        hSound_[i] = Audio::Load(audioList_[i].fileName, audioList_[i].isLoop, audioList_[i].maxPlayCount);
        assert(hSound_[i] >= 0);
    }

    // 初期音量設定
    InitVolume();
}

void AudioManager::InitVolume()
{
    // 設定ファイルから音量を取得
    gameVolume_ = GetPrivateProfileFloat("Audio", "GameVolume", 0, "./setup.ini");

    // ボリュームを0～100の範囲から、0.0f ～ 1.0fの範囲に変換する
    gameVolume_ /= 100.0f;
}

void AudioManager::SetVolume(float volume)
{
    // もし再設定したボリュームが範囲外だった時、0.0f ～ 1.0fの範囲に制限する
    if (volume < 0.0f)      volume = 0.0f;
    else if (volume > 1.0f) volume = 1.0f;

    // ボリュームを0.0f ～ 1.0fの範囲から、0～100の範囲に変換する
    gameVolume_ = volume * 100.0f;

    // 数値を文字列にする
    std::string volumeStr = std::to_string(static_cast<int>(gameVolume_));

    // 設定の音量を変更
    WritePrivateProfileString("Audio", "GameVolume", volumeStr.c_str(), "setup.ini");
}

void AudioManager::Play(AUDIO_ID id, float volume)
{
    Audio::Play(hSound_[id], gameVolume_ * volume);
}

void AudioManager::Stop(AUDIO_ID id)
{
    Audio::Stop(hSound_[id]);
}

void AudioManager::Release()
{
    Audio::Release();
}