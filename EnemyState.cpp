#include "EnemyState.h"
#include "EnemyBase.h"
#include "StateManager.h"

// �ҋ@���
EnemyIdleState::EnemyIdleState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyIdleState::EnterState()
{
    // �ҋ@�t���[��120���Z�b�g����
}

void EnemyIdleState::UpdateState()
{
    // �ҋ@�A�j���[�V�����Đ�

    // �ҋ@�t���[�������炷�B0�ɂȂ�����p�j��Ԃֈڍs

}

void EnemyIdleState::ExitState()
{
}


// �p�j���
EnemyWanderingState::EnemyWanderingState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyWanderingState::EnterState()
{
    // �T�m�Ԋu�t���[�����Z�b�g����

    /*
    �����_���Ȉړ����������߂�
    �߂�l�FXMVECTOR ����

    �����_���Ȉړ����������߂�
    �����F�ړ��͈�(�ŏ��ړ������A�ő�ړ�����)
    �߂�l�FXMVECTOR �ړ���
    */
}

void EnemyWanderingState::UpdateState()
{
    // ���s�A�j���[�V�����Đ�

    // �T�m�Ԋu�t���[����0�ɂȂ���
    /*
    ���E�Ƀv���C���[�����邩�𔻒肷��
    �G�l�~�[�̎��E�Ƀv���C���[�������Ă���Ƃ��͒ǐՏ�Ԃ�
    */

    // �G�l�~�[�̎��E�Ƀv���C���[�������Ă��Ȃ��Ƃ�
    /*
    ���߂�ꂽ�����Ɉړ�����
    �����F�ړ���*�����A�ړ����x
    �߂�l�F�Ȃ��A�ړ��������s��

    �v���C���[�Ƃ̋������v�Z����
    �����F���ݒn�A�ڕW�n
    �߂�l�F����

    �ǐՂ��邩�𔻒肷��
    �����F�����A���l
    �߂�l�F�^ or �U

    �^�������Ƃ��͒ǐՏ�Ԃ�
    */

    // �G�ƏՓ˂�����ʒu�𔼌a���ʒu�����炷

}

void EnemyWanderingState::ExitState()
{
}


// �ǐՏ��
EnemyChaseState::EnemyChaseState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyChaseState::EnterState()
{
}

void EnemyChaseState::UpdateState()
{
    // ���s�A�j���[�V����

    /*
    �v���C���[�܂ł̌o�H�����߂�
    �����F���ݒn�A�ڕW�l

    �ǐՂ��邩�𔻒肷��
    �����F�����A���l
    �߂�l�F�^ or �U

    �v���C���[�Ƃ̋������v�Z����
    �����F���ݒn�A�ڕW�n
    �߂�l�F����
    */

    // �U���͈͂ɂȂ�����U����Ԃ�
}

void EnemyChaseState::ExitState()
{
}


// �U�����
EnemyAttackState::EnemyAttackState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyAttackState::EnterState()
{
    // �U���N�[���^�C�����Z�b�g
}

void EnemyAttackState::UpdateState()
{
    // �U���N�[���^�C�������炷

    // �U���N�[���^�C����0�ɂȂ�����
    // �U���A�j���[�V�����Đ�
    // �^�_���[�W����

    // �U���͈͂��O�ꂽ��ǐՏ�Ԃ�

    // �U�����󂯂����_���[�W�X�e�[�g��
}

void EnemyAttackState::ExitState()
{
}


// ��_���[�W���
EnemyDamageState::EnemyDamageState(StateManager* manager) : StateBase(manager), pEnemyBase_(nullptr)
{
    pEnemyBase_ = static_cast<EnemyBase*>(pStateManager_->GetGameobject());
}

void EnemyDamageState::EnterState()
{
}

void EnemyDamageState::UpdateState()
{
    // ��e�A�j���[�V�����Đ�
    // ��_���[�W����

    
    // �U�����󂯂����e�A�j���[�V�����L�����Z�����s��
    // ��_���[�W�X�e�[�g��
}

void EnemyDamageState::ExitState()
{
}