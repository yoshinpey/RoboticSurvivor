#pragma once
#include "Engine/GameObject.h"
#include "CharacterBase.h"

// エネミーベースクラス
class EnemyBase :
    public GameObject,
    public CharacterBase
{
private:
    std::string name_; // エネミーの名前
    int id_;            // エネミーのID

public:
    EnemyBase();
    EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id);
    ~EnemyBase() override;
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    // エネミー固有の挙動
    void SpecialAttack();

    // 名前を取得
    std::string GetName() const{ return name_; }

    // IDを取得
    int GetId() const { return id_; };
};
