#include "Engine/Image.h"
#include "Gauge.h"

namespace
{
    // �摜���ǂݍ���
    std::vector<std::string> pictureName =
    {
        "Pictures/HitPoint_longFrame.png",
        "Pictures/HitPoint_long.png"
    };

    XMFLOAT3 positionOffset = { -0.95f,0.75f,0.0f };
    XMFLOAT3 scaleOffset = { 1.0f, 1.0f, 0.0f };
}

//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hpPict_{ -1,-1 },maxHp_(0),nowHp_(0)
{
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
    // �摜�ǂݍ���
    for (int i = 0; i < pictureName.size(); ++i)
    {
        hpPict_[i] = Image::Load(pictureName[i]);
        assert(hpPict_[i] >= 0);
    }

    // �ʒu����
    transform_.position_ = positionOffset;
    // �T�C�Y����
    transform_.scale_ = scaleOffset;
}

//�X�V
void Gauge::Update()
{
}

//�`��
void Gauge::Draw()
{
    //�o�[�̕\��
    Transform transGauge = transform_;
    transGauge.scale_.x = nowHp_ / maxHp_;

    // �ő�HP�Q�[�W
    Image::SetTransform(hpPict_[0], transform_);
    Image::Draw(hpPict_[0]);
    // �c��HP�Q�[�W
    Image::SetTransform(hpPict_[1], transGauge);
    Image::Draw(hpPict_[1]);


}

//�J��
void Gauge::Release()
{
}