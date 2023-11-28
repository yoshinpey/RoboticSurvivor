#pragma once

// �L�����N�^�[�̃X�e�[�^�X���Ǘ�����N���X
class CharacterBase
{
private:
    // �L�����N�^�[�̃X�e�[�^�X
    int maxHp_;         // �̗�
    int attackPower_;   // �U����

    // �ړ��֘A�̃p�����[�^
    float jumpVelocity_; // �W�����v�̏����x
    float walkSpeed_;    // ���s���x
    float runSpeed_;     // ���s���x

public:
    CharacterBase();
    ~CharacterBase();

    ///////////////////////////�Z�b�^�[///////////////////////////
    
    // �L�����N�^�[�̃X�e�[�^�X���Z�b�g
    void SetCharacterStatus(int maxHp, int attackPower);

    // �ړ��֘A�̃p�����[�^���Z�b�g
    void SetMovementParameters(float jumpVelocity, float walkSpeed, float runSpeed);

    ///////////////////////////�Q�b�^�[///////////////////////////
    
    // �U���͎擾
    int GetAttackPower() const { return attackPower_; }

    // �̗͎擾
    int GetMaxHp() const { return maxHp_; }

    // �����͎擾
    float GetJumpVelocity() const { return jumpVelocity_; }

    // ���s���x�擾
    float GetWalkSpeed() const { return walkSpeed_; }

    // ���s���x�擾
    float GetRunSpeed() const { return runSpeed_; }
};