#include "Enemy_Ground.h"

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

}

void Enemy_Ground::Update()
{
    // �������l�������Ă��邩�m�F�B�f�o�b�N
    OutputDebugStringA(std::to_string(walkSpeed_).c_str());
    OutputDebugString("\n");
    transform_.position_.x += walkSpeed_;
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
    ////////////////////����C���N���[�h
    // #include "pugixml.hpp"
    // 
    /////////////////////////////����R���X�g���N�^
    // XML�t�@�C������X�e�[�^�X��ǂݍ���
    // �Ȃ����f�[�^����񂩂���
    //loadStatsFromXML("EnemySettings.xml");
    // 
    /////////////////////���ꂱ�̂܂�
    //pugi::xml_document doc;
    //if (!doc.load_file(filename.c_str())) {
    //    // XML�t�@�C���̓ǂݍ��݂Ɏ��s�����ꍇ�̏���
    //    return;
    //}
    //// XML�m�[�h����X�e�[�^�X���擾
    //pugi::xml_node rootNode = doc.child("Enemy_Ground");
    //if (!rootNode) {
    //    // Enemy_Ground�m�[�h��������Ȃ������ꍇ�̏���
    //    return;
    //}
    //walkSpeed_ = std::stof(rootNode.child("walkSpeed").text().get());
    //attackPower_ = std::stof(rootNode.child("attackPower").text().get());
    //attackCooldown_ = std::stof(rootNode.child("attackCooldown").text().get());
}

// JSON�t�@�C���������������ǂݍ��ފ֐�
float Enemy_Ground::LoadWalkSpeedFromJson(const std::string& filename)
{
    ////////////////////����C���N���[�h
    //#include <fstream>
    //#include "picojson.h"
    //////////////////////////����R���X�g���N�^
    // JSON�t�@�C���������������ǂݍ���
    //walkSpeed_ = LoadWalkSpeedFromJson("EnemySettings.json");
    ///////////////////////////���ꂱ�̂܂�
    //picojson::value json_data;
    //// JSON�t�@�C����ǂݍ���
    //std::ifstream file("EnemySettings.json");
    //if (!file.is_open()) {
    //    return;
    //}
    //// picojson::value��JSON�f�[�^���p�[�X����
    //file >> json_data;
    //file.close();
    //// JSON�I�u�W�F�N�g����Enemy_Ground�̕����������擾����
    //// �����������擾���ă����o�ϐ��ɐݒ肷��
    //walkSpeed_ = json_data.get<picojson::object>()
    //    ["Enemy_Ground"].get<picojson::object>()
    //    ["walk_speed"].get<double>();
}