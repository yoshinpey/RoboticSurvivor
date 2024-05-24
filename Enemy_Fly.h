#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"
#include <unordered_set>

class Player;

//���V�G���Ǘ�����N���X
class Enemy_Fly : public EnemyBase
{
    int hModel_;                        // ���f���ԍ�
    XMFLOAT3 currentPosition_;          // ���ݒn

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

};