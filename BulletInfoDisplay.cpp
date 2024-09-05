#include "BulletInfoDisplay.h"
#include "Engine/Image.h"

void BulletInfoDisplay::Initialize()
{
    // 画像のパス
    std::vector<std::string> numPicturePaths;
    for (int i = 0; i <= 9; ++i)
    {
        std::string path = "IMG/Number/" + std::to_string(i) + ".png";
        numPicturePaths.push_back(path);
    }

    // 画像データのロード
    for (const auto& path : numPicturePaths)
    {
        int handle = Image::Load(path);
        assert(handle >= 0);
        hPict_.push_back(handle);
    }

    // 画像のサイズを取得してウィンドウに合わせる
    XMFLOAT3 size = Image::GetTextureSize(hPict_[0]); // "0"のサイズを基準に
    transform_.scale_.x = Direct3D::screenWidth_ / size.x * 0.2f;
    transform_.scale_.y = Direct3D::screenHeight_ / size.y * 0.2f;
    transform_.z = 0.0f;

    // 表示位置を右上に設定
    basePosition_.x = Direct3D::screenWidth_ - size.x * transform_.scale_.x * 3;
    basePosition_.y = size.y * transform_.scale_.y;
}

void BulletInfoDisplay::Update(const std::vector<int>& bulletInfoList_)
{
    // 弾丸情報を更新
    currentBulletCount_ = bulletInfoList_;
}

void BulletInfoDisplay::Draw()
{
    int posX = 50;  // 初期のX座標
    int posY = 50;  // 初期のY座標

    // 各弾丸数を画像として表示
    for (size_t i = 0; i < currentBulletCount_.size(); ++i)
    {
        int bulletCount = currentBulletCount_[i];

        // 各桁の数字を画像で描画
        if (bulletCount >= 0 && bulletCount <= 9)
        {
            DrawNumber(bulletCount, posX, posY);
        }

        // 表示位置をずらす
        posX += 30; // 次の数字を少し右に表示
    }
}

void BulletInfoDisplay::DrawNumber(int number, int positionX, int positionY)
{
    if (number >= 0 && number < hPict_.size())
    {
        // 画像の位置を設定
        textTrans_.position_.x = static_cast<float>(positionX);
        textTrans_.position_.y = static_cast<float>(positionY);

        // 画像の描画設定
        Image::SetTransform(hPict_[number], transform_);
        Image::Draw(hPict_[number]);
    }
}
