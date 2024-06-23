#pragma once
#include "Engine/GameObject.h"

class Text;

//�^�C�}�[�Ǘ�����N���X
class Timer : public GameObject
{
    bool active_;        // �N�����Ă��邩�ǂ���
    float frame_;        // �t���[����
    Text* pNum_;         // �e�L�X�g�\���p
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
