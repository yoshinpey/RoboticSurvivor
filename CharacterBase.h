#pragma once

// �L�����N�^�[�̃X�e�[�^�X���Ǘ�����N���X
class CharacterBase
{
protected:
    int maxHp_;          // �̗�
    float jumpVelocity_; // �W�����v�̏����x
    float walkSpeed_;    // ���s���x
    float runSpeed_;     // ���s���x

    int attackPower_; // �U����

public:
    CharacterBase();
    virtual ~CharacterBase();

    // ���ׂẴL�����N�^�[�����p�����[�^
    virtual void SetStatus(int maxHp, float jumpVelocity, float walkSpeed, float runSpeed);

    // �U����
    void SetAttackPower(int attackPower);

    // �̗͎擾
    int GetMaxHp() const { return maxHp_; }

    // �����͎擾
    float GetJumpVelocity() const { return jumpVelocity_; }

    // ���s���x�擾
    float GetWalkSpeed() const { return walkSpeed_; }

    // ���s���x�擾
    float GetRunSpeed() const { return runSpeed_; }

    // �U���͎擾
    int GetAttackPower() const { return attackPower_; }
};