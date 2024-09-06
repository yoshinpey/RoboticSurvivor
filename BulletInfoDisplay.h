// BulletInfoDisplay.h
#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <string>
#include <cassert>
#include "Engine/Image.h"

class BulletInfoDisplay
{
private:
    // 数字の画像ハンドルのリスト
    std::vector<int> hPict_;

    // 表示する弾丸数
    int bulletCount_;

    Transform transform_;
    Transform textTrans_;

public:
    // 初期化処理
    void Initialize();

    // 更新処理：弾丸の数を設定する
    void Update(int bulletCount);

    // 描画処理：弾丸の数を画像で表示する
    void Draw();

    // 画像を表示するための補助関数
    void DrawNumber(int number, int positionX, int positionY);
};
