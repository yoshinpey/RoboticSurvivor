#include "Enemy_Fly.h"

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pCollision_(nullptr)
{
    // �v���C���[�̃X�e�[�^�X��ݒ�
    //characterStatus_.SetCharacterStatus(MAX_HP, ATK);
    //characterStatus_.SetMovementParameters(JUMP_HEIGHT, WALK_SPEED, RUN_SPEED);

}

Enemy_Fly::~Enemy_Fly()
{
}

void Enemy_Fly::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Enemy.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // �����蔻��t�^
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 1.5f);
    AddCollider(pCollision_);
}

void Enemy_Fly::Update()
{
    // �R���W�����̑傫�������f���ɍ��킹��
    // pCollision_->SetRadius(transform_.scale_.x);
}

void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Fly::Release()
{
}

void Enemy_Fly::OnCollision(GameObject* pTarget)
{
    /*
    // �e�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Fly::Attack()
{
}

/*
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
void Enemy_Ground::LoadWalkSpeedFromJson(const std::string& filename)
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
*/
