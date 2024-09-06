// BulletInfoDisplay.cpp
#include "BulletInfoDisplay.h"

void BulletInfoDisplay::Initialize()
{
    // 画像のパス
    for (int i = 0; i <= 9; ++i)
    {
        std::string path = "IMG/Number/" + std::to_string(i) + ".png";
        int hPict = Image::Load(path);
        assert(hPict >= 0);
        hPict_.push_back(hPict);
    }

    // 画像のサイズを取得してウィンドウに合わせる
    XMFLOAT3 size = Image::GetTextureSize(hPict_[0]); // "0"のサイズを基準に
    transform_.scale_.x = Direct3D::screenWidth_ / size.x * 0.2f;
    transform_.scale_.y = Direct3D::screenHeight_ / size.y * 0.2f;
    transform_.scale_.z = 0.0f;
}

void BulletInfoDisplay::Update(int bulletCount)
{
    bulletCount_ = bulletCount;
}

void BulletInfoDisplay::Draw()
{
    // 弾丸数を描画するための位置
    int posX = 50; // 初期のX座標
    int posY = 50; // 初期のY座標

    // 各桁の数字を画像として表示
    if (bulletCount_ == 0)
    {
        DrawNumber(0, posX, posY);
    }
    else
    {
        int num = bulletCount_;
        std::vector<int> digits;

        // 数字を桁ごとに分解して保存する
        while (num > 0)
        {
            digits.push_back(num % 10);
            num /= 10;
        }

        // 数字の桁数が逆順なので、逆順に表示
        for (int i = digits.size() - 1; i >= 0; --i)
        {
            DrawNumber(digits[i], posX, posY);
            posX += 30; // 次の数字を少し右に表示
        }
    }
}

void BulletInfoDisplay::DrawNumber(int number, int positionX, int positionY)
{
    if (number >= 0 && number < hPict_.size())
    {
        Transform textTrans = transform_;
        textTrans.position_.x = static_cast<float>(positionX);
        textTrans.position_.y = static_cast<float>(positionY);

        // 画像の描画設定
        Image::SetTransform(hPict_[number], textTrans);
        Image::Draw(hPict_[number]);
    }
}
