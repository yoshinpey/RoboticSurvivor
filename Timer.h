#pragma once
#include "Engine/GameObject.h"

class Text;

//タイマー管理するクラス
class Timer : public GameObject
{
    bool active_;        // 起動しているかどうか
    float frame_;        // フレーム数
    Text* pNum_;         // テキスト表示用
    const int FPS = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");

public:
    Timer(GameObject* parent);
    ~Timer();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    int GetFrame() const { return frame_; }
    void SetLimit(float seconds) { frame_ = seconds * FPS; }
    void Start() { active_ = true; }
    void Stop() { active_ = false; }
    void Reset() { frame_ = 0; }
    bool IsFinished() { return (frame_ <= 0); }
};
