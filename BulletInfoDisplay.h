// BulletInfoDisplay.h
#pragma once
#include "Engine/GameObject.h"
#include <vector>

class BulletInfoDisplay : public GameObject
{
private:
    enum NumPic
    {
        Num0,  // 0.png
        Num1,  // 1.png
        Num2,  // 2.png
        Num3,  // 3.png
        Num4,  // 4.png
        Num5,  // 5.png
        Num6,  // 6.png
        Num7,  // 7.png
        Num8,  // 8.png
        Num9,  // 9.png
        Slash  // Slash.png
    };
    // 数字の画像ハンドルのリスト
    std::vector<int> hPict_;
    int missileIconHandle_;

    // 表示する弾丸数
    int bulletCount_;
    int currentMagazine_;   //マガジン容量
    int maxMagazine_;       //最大マガジン容量

public:
    BulletInfoDisplay(GameObject* parent);
    ~BulletInfoDisplay() override;
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void DrawBullet();
    void SetMaxMagazine(int mag) { maxMagazine_ = mag; }
    void SetCurrentMagazine(int mag) { currentMagazine_ = mag; }
};
