#include "EnemySpawn.h"

#include "EnemyManager.h"

EnemySpawn::EnemySpawn(EnemyManager* enemyManager) : pEnemyManager_(enemyManager)
{
}

EnemySpawn::~EnemySpawn()
{
}


void EnemySpawn::SpawnEnemiesForWave(const nlohmann::json& waveData)
{
    // waveData����G�̏o���f�[�^���擾���AEnemyManager���g�p���ēG�𐶐����鏈������������
    // �Ⴆ�΁AwaveData����o�������GID�⑍���A�ŏ����W�A�ő���W���擾���AEnemyManager�̓K�؂Ȋ֐����Ăяo��
    int enemyID = waveData["�o�������GID"];
    int totalEnemies = waveData["�o�������G�̑���"];
    auto minPosition = waveData["�o�������G�̍ŏ����W(XYZ)"];
    auto maxPosition = waveData["�o�������G�̍ő���W(XYZ)"];

    // �G�̏o������
    XMFLOAT3 minPos(minPosition[0], minPosition[1], minPosition[2]);
    XMFLOAT3 maxPos(maxPosition[0], maxPosition[1], maxPosition[2]);
    pEnemyManager_->SpawnMultiEnemy(minPos, maxPos, totalEnemies, static_cast<EnemyType>(enemyID));
}

void EnemySpawn::SpawnEnemiesFromJSON(const std::string& filename)
{
    // JSON�t�@�C������E�F�[�u�f�[�^��ǂݍ��݁A�G�𐶐�����
    JsonReader::Load(filename);

    for (int waveIndex = 0; ; ++waveIndex)
    {
        std::string waveKey = "wave" + std::to_string(waveIndex);
        if (JsonReader::GetSection(waveKey).empty())
        {
            // �E�F�[�u��������Ȃ��ꍇ�A�ǂݍ��ݏI��
            break;
        }
        SpawnEnemiesForWave(JsonReader::GetSection(waveKey));
    }
}