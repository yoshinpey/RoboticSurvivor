#pragma once
#include "Engine/GameObject.h"
#include "CharacterBase.h"

// エネミーベースクラス
class EnemyBase :
    public GameObject,
    public CharacterBase
{
private:
    // エネミー固有の属性や挙動を追加する変数やメソッド

public:
    // デフォルトコンストラクタ
    EnemyBase();

    // 引数を持つコンストラクタ
    EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id);

    // デストラクタ
    ~EnemyBase() override;

    // 純粋仮想関数をオーバーライド
    void Update() override;

    // エネミー固有のメソッドや挙動を追加
    void SpecialAttack();

    // Initialize、Draw、Release メソッドのオーバーライド
    void Initialize() override;
    void Draw() override;
    void Release() override;
};
