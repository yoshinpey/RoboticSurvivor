#pragma once

class StateManager;
class Player;

// ��ԃx�[�X�N���X
class StateBase
{   
protected:
    StateManager* pStateManager_;
    Player* pPlayer_;
public:
    StateBase(StateManager* manager) 
        : pStateManager_(manager), pPlayer_(nullptr)
    {
    }

    // �f�X�g���N�^
    virtual ~StateBase() {};
    // ��Ԃɓ���Ƃ��̏�����
    virtual void EnterState() = 0;
    // ��Ԃ̍X�V
    virtual void UpdateState() = 0;
    // ��Ԃ���o��Ƃ��̌㏈��
    virtual void ExitState() = 0;
};