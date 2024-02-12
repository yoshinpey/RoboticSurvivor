#include "Enemy_Ground.h"
#include "pugixml.hpp"

#include <fstream>
#include "picojson.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr), walkSpeed_(0)
{
}

Enemy_Ground::~Enemy_Ground()
{
}

void Enemy_Ground::Initialize()
{
    // ���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Enemy_02.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // �����蔻��t�^
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 2.0f);
    AddCollider(pCollision_);

    picojson::value json_data;
    // JSON�t�@�C����ǂݍ���
    std::ifstream file("EnemySettings.json");
    if (!file.is_open()) {
        return;
    }

    // picojson::value��JSON�f�[�^���p�[�X����
    file >> json_data;
    file.close();

    // JSON�I�u�W�F�N�g����Enemy_Ground�̕����������擾����
    // �����������擾���ă����o�ϐ��ɐݒ肷��
    walkSpeed_ = json_data.get<picojson::object>()
        ["Enemy_Ground"].get<picojson::object>()
        ["walk_speed"].get<double>();

}

void Enemy_Ground::Update()
{
    // �������l�������Ă��邩�m�F
    OutputDebugStringA(std::to_string(walkSpeed_).c_str());
    OutputDebugString("\n");

    if (walkSpeed_ != 0)
        transform_.position_.x += 0.1f;

    // ����ς�f�[�^������Ȃ�

}

void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{
    /*
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Ground::Attack()
{
}

void Enemy_Ground::loadStatsFromXML(const std::string& filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str())) {
        // XML�t�@�C���̓ǂݍ��݂Ɏ��s�����ꍇ�̏���
        return;
    }

    // XML�m�[�h����X�e�[�^�X���擾
    pugi::xml_node rootNode = doc.child("Enemy_Ground");
    if (!rootNode) {
        // Enemy_Ground�m�[�h��������Ȃ������ꍇ�̏���
        return;
    }

    walkSpeed_ = std::stof(rootNode.child("walkSpeed").text().get());
    attackPower_ = std::stof(rootNode.child("attackPower").text().get());
    attackCooldown_ = std::stof(rootNode.child("attackCooldown").text().get());

    // XML�t�@�C������X�e�[�^�X��ǂݍ���
    // ����R���X�g���N�^�ŌĂԁB�Ȃ����f�[�^����񂩂���
    //loadStatsFromXML("EnemySettings.xml");
}