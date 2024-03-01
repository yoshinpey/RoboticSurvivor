#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

//���V�G���Ǘ�����N���X
class Enemy_Fly : public EnemyBase
{
    int hModel_;                        // ���f���ԍ�
    SphereCollider* pCollision_;        // �R���W����
    //SphereCollider* pHeadCollision_;        // �R���W����

public:
    Enemy_Fly(GameObject* parent);      // �R���X�g���N�^
    ~Enemy_Fly();                       // �f�X�g���N�^
    void Initialize() override;         // ������
    void Update() override;             // �X�V
    void Draw() override;               // �`��
    void Release() override;            // �J��

    // �����ɓ�������
    void OnCollision(GameObject* pTarget) override;

    //void HeadOnCollision(GameObject* pTarget) override;

    void Attack() override;

   
};