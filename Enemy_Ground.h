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
    Enemy_Ground(GameObject* parent);

    // �f�X�g���N�^
    ~Enemy_Ground() override;

    // ������
    void Initialize() override;

    // �X�V
    void Update() override;

    // �`��
    void Draw() override;

    // �J��
    void Release() override;
};
