#pragma once
#include "EnemyBase.h"

class Player;

// �n��G���Ǘ�����N���X
class Enemy_Explosion : public EnemyBase
{
    int hModel_;                    // ���f���ԍ�
    XMFLOAT3 pastPosition_;      // ���ݒn

public:
    Enemy_Explosion(GameObject* parent);    // �R���X�g���N�^
    ~Enemy_Explosion() override;            // �f�X�g���N�^
    void Initialize() override;             // ������
    void Update() override;                 // �X�V
    void Draw() override;                   // �`��
    void Release() override;                // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    // �U��
    void Attack() override;

};
