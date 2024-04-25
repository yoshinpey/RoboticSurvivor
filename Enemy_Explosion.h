#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"
#include <unordered_set>

class Player;

// �n��G���Ǘ�����N���X
class Enemy_Explosion : public EnemyBase
{
    int hModel_;                    // ���f���ԍ�
    float currentHp_;               // ���݂�HP 

    // �q�b�g�����G�̃f�[�^�����Ă���
    std::unordered_set<GameObject*> hitEnemies;

public:
    Enemy_Explosion(GameObject* parent);   // �R���X�g���N�^
    ~Enemy_Explosion() override;           // �f�X�g���N�^
    void Initialize() override;             // ������
    void Update() override;                 // �X�V
    void Draw() override;                   // �`��
    void Release() override;                // �J��

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
