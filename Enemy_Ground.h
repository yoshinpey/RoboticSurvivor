#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// �n��G���Ǘ�����N���X
class Enemy_Ground : public EnemyBase
{
    int hModel_;  // ���f���ԍ�
    SphereCollider* pCollision_;

    // �\���̂̃C���X�^���X
    EnemyStatus status_;
    EnemyAlgorithm algorithm_;

public:
    Enemy_Ground(GameObject* parent);   // �R���X�g���N�^
    ~Enemy_Ground() override;           // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V
    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget);

    void Attack() override;

    /*
    void loadStatsFromXML(const std::string& filename);
    void LoadWalkSpeedFromJson(const std::string& filename);
    */

};
