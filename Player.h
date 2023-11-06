#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;                //���f���ԍ�   
    int maxHp_, nowHp_;         //HP 

    float jampVelocity_;        //�W�����v���x
    float fuel_;                //�R��
    float maxFuel_;             //�ő�R��
    float jumpCool_;            //�N�[���^�C��
    float gravity_;             //�d��
    bool CanJump_;              //�W�����v�\��

    Text* pNum;                 //�e�L�X�g

public:
    Player(GameObject* parent);     //�R���X�g���N�^
    ~Player();                      //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
    
    //�A�N�V����
    void Move();                    //�v���C���[�̈ړ�
    void Jump();                    //�W�����v
    void JetPack();                 //�W�F�b�g�p�b�N
    void BoostJump();               //�g�ݍ��킹
    void PlayerHitPoint();          //�̗�
    void CameraPosition();          //���_

    //�v���C���[���W�̃Q�b�^�[
    XMFLOAT3 GetPlaPos() { return transform_.position_; }

};