#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//�^�C�}�[�Ǘ�����N���X
class Timer : public GameObject
{
    bool Active;        //�N�����Ă��邩�ǂ���
    int Frame;          //��b�Ԃɉ���X�V����邩
    Text* pNum;         //�b���e�L�X�g
    float drawX;        //�`��ʒu(���E)
    float drawY;        //�`�捂��

public:
    Timer(GameObject* parent);      //�R���X�g���N�^
    ~Timer();                       //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    //�^�C�}�[�ݒ�
    void SetLimit(float seconds);

    //�^�C�}�[�J�n
    void Start();

    //�^�C�}�[�I��
    void Stop();

    //�^�C�}�[�����I��
    bool IsFinished();
};