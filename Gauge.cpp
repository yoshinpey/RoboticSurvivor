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
    :UIBase(parent, "Gauge"), maxHp_(0), nowHp_(0)
{
    // �摜�ǂݍ���
    hPict_.resize(pictureName.size());
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
        hPict_[i] = Image::Load(pictureName[i]);
        assert(hPict_[i] >= 0);
    }

    // �ʒu����
    transform_.position_ = positionOffset;
    // �T�C�Y����
    transform_.scale_ = scaleOffset;

    // �Q�[�W�t���[���摜�̃T�C�Y�擾
    XMFLOAT3 size = Image::GetTextureSize(hPict_[FRAME]);

    // �摜�̔z�u�F-1�����[�A0�������A1���E�[
    // �E�B���h�E�ɍ��킹��
    transform_.scale_.x = (Direct3D::screenWidth_ / size.x) * scaleOffset.x;
    transform_.scale_.y = scaleOffset.y;                                        // Y���̃X�P�[���͌Œ�l
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
    transGauge.scale_.x *= nowHp_ / maxHp_;

    // �ő�HP�Q�[�W
    Image::SetTransform(hPict_[FRAME], transform_);
    Image::Draw(hPict_[FRAME]);

    // �c��HP�Q�[�W
    Image::SetTransform(hPict_[GAUGE], transGauge);
    Image::Draw(hPict_[GAUGE]);
}

//�J��
void Gauge::Release()
{
}