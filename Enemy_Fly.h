#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

class Player;

//���V�G���Ǘ�����N���X
class Enemy_Fly : public EnemyBase
{
    int hModel_;                        // ���f���ԍ�
    bool isFirstHit_;               // ����q�b�g�t���O
    XMFLOAT3 firstPosition_;        // �e�e�q�b�g�ʒu�ۑ��p

public:
    Enemy_Fly(GameObject* parent);      // �R���X�g���N�^
    ~Enemy_Fly();                       // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V
    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    // �U��
    void Attack() override;

    // HP���擾
    float GetCurrentHp() const override { return currentHp_; }

    // HP�𑝂₷
    void IncreaseHp(float amount) override;

    // HP�����炷
    void DecreaseHp(float amount) override;

    // ���S����
    bool IsDead() const override { return currentHp_ <= 0; }
};