#pragma once
#include "UIBase.h"

//HP���Ǘ�����N���X
class Gauge : public UIBase
{
    // �e�L�X�g�摜�̓��e
    enum
    {
        FRAME = 0,
        GAUGE
    };
    std::vector<int> hPict_;    // �摜�ԍ�

    float maxHp_;               // �ő�HP
    float nowHp_;               // ���݂�HP

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