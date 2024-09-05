// BulletInfoDisplay.h
#pragma once
#include "Engine/GameObject.h"

class BulletInfoDisplay
{
public:
    // 初期化処理
    void Initialize();

    // 更新処理：弾丸の数を更新する
    void Update(const std::vector<int>& bulletInfoList_);

    // 描画処理：弾丸の数を画像で表示する
    void Draw();

private:
    // 画像ハンドルのリスト
    std::vector<int> hPict_;

    // 表示位置
    Transform transform_;
    Transform textTrans_;

    // 表示する弾丸情報のリスト
    std::vector<int> currentBulletCount_;

    // 画像を表示するための補助関数
    void DrawNumber(int number, int positionX, int positionY);

    // 弾丸数表示の基準位置
    XMFLOAT2 basePosition_;
};