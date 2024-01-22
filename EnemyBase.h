#pragma once
#include "Engine/GameObject.h"
#include "CharacterBase.h"

// �G�l�~�[�x�[�X�N���X
class EnemyBase :
    public GameObject,
    public CharacterBase
{
private:
    std::string name_; // �G�l�~�[�̖��O
    int id_;            // �G�l�~�[��ID

public:
    EnemyBase();
    EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id);
    ~EnemyBase() override;
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    // �G�l�~�[�ŗL�̋���
    void SpecialAttack();

    // ���O���擾
    std::string GetName() const{ return name_; }

    // ID���擾
    int GetId() const { return id_; };
};
