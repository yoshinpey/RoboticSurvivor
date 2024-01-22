#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// �n��G���Ǘ�����N���X
class Enemy_Ground : public EnemyBase
{
private:
    int hModel_;  // ���f���ԍ�

public:
    // �R���X�g���N�^
    Enemy_Ground(GameObject* parent, const XMFLOAT3& spawnPosition);

    // �f�X�g���N�^
    ~Enemy_Ground();

    // ������
    void Initialize() override;

    // �X�V
    void Update() override;

    // �`��
    void Draw() override;

    // �J��
    void Release() override;

    // GetName�̎���
    std::string GetName() const
    {
        // �����ɖ��O���擾���鏈����ǉ�
        return "GroundEnemy";
    }

    // GetId�̎���
    int GetId() const
    {
        // ������ID���擾���鏈����ǉ�
        return 1;
    }
};