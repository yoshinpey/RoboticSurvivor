#pragma once
#include "Engine/GameObject.h"

//�n�ʃ��f�����Ǘ�����N���X
class Ground : public GameObject
{
    int hModel_;    //���f���ԍ�

public:
    Ground(GameObject* parent);     //�R���X�g���N�^
    ~Ground();                      //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    //�����蔻��
    void OnCollision(GameObject* pTarget) override;
};