#pragma once
#include "Engine/GameObject.h"

//HP���Ǘ�����N���X
class Gauge : public GameObject
{
    int hpPict_[2];    //�摜�ԍ�
    float maxHp_, nowHp_;

public:
    Gauge(GameObject* parent);      //�R���X�g���N�^
    ~Gauge();                       //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    //HP�Z�b�^�[
    void SetHp(float maxHp, float nowHp)
    {
        maxHp_ = maxHp;
        nowHp_ = nowHp;
    }
};