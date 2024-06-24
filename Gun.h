
#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Player;
enum class BulletType;

// �o���b�g�̏���ۊǂ���\����
struct BulletInfo
{
    int coolTime_;
};

//�e���Ǘ�����N���X
class Gun : public GameObject
{
    int hModel_;                    // ���f���ԍ�
    XMFLOAT3 moveDirection_;        // ��������
    Player* pPlayer_;
    // �o���b�g�̃��X�g
    std::vector<BulletInfo> bulletInfoList_;

    int flickerTimer_;              // ���G��Ԃ̂�����^�C�}�[
public:
    Gun(GameObject* parent);
    ~Gun();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // �e�e�̑��x�Ǝˏo�������v�Z����
    XMFLOAT3 CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed);

    // �e�e�𐶐�����
    template<class T>
    void ShootBullet(BulletType type);

    // �ړ������擾
    XMFLOAT3 GetMoveDirection() const { return moveDirection_; }
    void InputConfirmation();
};
