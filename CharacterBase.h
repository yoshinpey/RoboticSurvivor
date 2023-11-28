#pragma once
class CharacterBase
{
protected:
    int maxHp_;          // �̗�
    float jumpVelocity_; // �W�����v�̏����x
    float walkSpeed_;    // ���s���x
    float runSpeed_;     // ���s���x

public:
    CharacterBase();
    virtual ~CharacterBase();

    void SetStatus(int maxHp, float jumpVelocity, float walkSpeed, float runSpeed);
};