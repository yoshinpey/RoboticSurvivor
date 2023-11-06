#include "Engine/Image.h"
#include "Gauge.h"

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
    //���g
    hpPict_[0] = Image::Load("HitPoint.png");
    assert(hpPict_[0] >= 0);
    //�g
    hpPict_[1] = Image::Load("HitPointFrame.png");
    assert(hpPict_[1] >= 0);

    //�ʒu����
    transform_.position_.x = -0.95;
    transform_.position_.y = 0.75;
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
    transGauge.scale_.x = (float)nowHp_ / (float)maxHp_;

    Image::SetTransform(hpPict_[0], transGauge);
    Image::Draw(hpPict_[0]);

    Image::SetTransform(hpPict_[1], transform_);
    Image::Draw(hpPict_[1]);
}

//�J��
void Gauge::Release()
{
}