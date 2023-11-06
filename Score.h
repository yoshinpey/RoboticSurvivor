#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Score���Ǘ�����N���X
class Score : public GameObject
{
    Text* pText;    //�e�L�X�g
    int score_;     //�X�R�A
    float drawX_;    //�`��ʒu(���E)
    float drawY_;    //�`�捂��

public:
    Score(GameObject* parent);      //�R���X�g���N�^
    ~Score();                       //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    // �X�R�A�����Z����
    void ScoreAdd(int score);            // �X�R�A�����Z����
    int GetScore();                // �X�R�A���擾����
};