#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

class Player;

// 視点を管理するクラス
class Aim : public GameObject
{
    const float EYE_POSITION = 2.0f;

    XMFLOAT3 aimDirection_;
    XMFLOAT3 camPos_;
    XMFLOAT3 eyePositon_;
    XMFLOAT2 mouseSensitivity_;
    Text* pNum_;
    Player* pPlayer_;

    void UpdateRotation();
    void UpdateCameraPosition();

public:
    Aim(GameObject* parent);        //コンストラクタ
    ~Aim();                         //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    //進行方向ベクトルのAim情報を取得
    XMFLOAT3 GetAimDirection(){ return aimDirection_; }
    XMFLOAT3 GetEyePosition(){ return eyePositon_; }
};