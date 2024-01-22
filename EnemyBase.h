#pragma once
#include "Engine/GameObject.h"
#include "CharacterBase.h"

// �G�l�~�[�x�[�X�N���X
class EnemyBase :
    public GameObject,
    public CharacterBase
{
private:
    // �G�l�~�[�ŗL�̑����⋓����ǉ�����ϐ��⃁�\�b�h

public:
    // �f�t�H���g�R���X�g���N�^
    EnemyBase();

    // ���������R���X�g���N�^
    EnemyBase(const DirectX::XMFLOAT3& spawnPosition, const std::string& name, int id);

    // �f�X�g���N�^
    ~EnemyBase() override;

    // �������z�֐����I�[�o�[���C�h
    void Update() override;

    // �G�l�~�[�ŗL�̃��\�b�h�⋓����ǉ�
    void SpecialAttack();

    // Initialize�ADraw�ARelease ���\�b�h�̃I�[�o�[���C�h
    void Initialize() override;
    void Draw() override;
    void Release() override;
};
