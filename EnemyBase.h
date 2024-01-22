#pragma once
#include "Engine/GameObject.h"
#include "CharacterBase.h"

// �G�l�~�[�x�[�X�N���X
class EnemyBase :
    public GameObject,
    public CharacterBase
{
private:
    std::string name_;  // �G�l�~�[�̖��O
    int id_;            // �G�l�~�[��ID

public:
    // �f�t�H���g�R���X�g���N�^
    EnemyBase();

    // ��������R���X�g���N�^
    EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id);

    // �f�X�g���N�^
    ~EnemyBase() override;

    // ������
    void Initialize() override;

    // �X�V
    void Update() override;

    // �`��
    void Draw() override;

    // �J��
    void Release() override;

    // �G�l�~�[�ŗL�̋���
    void SpecialAttack();

    // ���O���擾
    std::string GetName() const { return name_; }

    // ID���擾
    int GetId() const { return id_; };
};
