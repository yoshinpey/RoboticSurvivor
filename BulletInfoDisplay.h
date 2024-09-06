// BulletInfoDisplay.h
#pragma once
#include "Engine/GameObject.h"
#include <vector>

class BulletInfoDisplay : public GameObject
{
private:
    enum {
        CENTER = 0,
    };
    // 数字の画像ハンドルのリスト
    std::vector<int> hPict_;

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
