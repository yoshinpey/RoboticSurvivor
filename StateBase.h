#pragma once

// ��ԃx�[�X�N���X
class StateBase
{
public:
    // �f�X�g���N�^
    virtual ~StateBase() {};

    // ��Ԃɓ���Ƃ��̏�����
    virtual void EnterState() = 0;

    // ��Ԃ̍X�V
    virtual void UpdateState() = 0;

    // ��Ԃ���o��Ƃ��̌㏈��
    virtual void ExitState() = 0;
};
