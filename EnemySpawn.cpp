#include "EnemySpawn.h"
#include <random>

#include "Player.h"


// �R���X�g���N�^�̎���
EnemySpawn::EnemySpawn(EnemyManager* enemyManager, Player* player, int waveTimer, int maxWaves)
    : enemyManager_(enemyManager), player_(player), waveTimer_(waveTimer), waveCount_(0), maxWaves_(maxWaves) {}

// �E�F�[�u�̃X�|�[�������̎���
void EnemySpawn::SpawnWave() {
    // �����_���Ȉʒu�ɓG���X�|�[��������
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(-20.0f, 20.0f);
    std::uniform_real_distribution<float> disZ(-20.0f, 20.0f);

    // �����_���Ȉʒu���v�Z
    XMFLOAT3 spawnPosition(disX(gen), 0.0f, disZ(gen));

    // �����_���Ȏ�ނ̓G���X�|�[��������
    EnemyType enemyType = static_cast<EnemyType>(rand() % static_cast<int>(EnemyType::MAX));

    // �G���X�|�[��������
    enemyManager_->SpawnEnemy(spawnPosition, enemyType);
}

// �E�F�[�u�̍X�V�����̎���
void EnemySpawn::UpdateWave() {
    waveTimer_--; // �^�C�}�[�����炷

    // �^�C�}�[��0�ȉ��ɂȂ�����V�����E�F�[�u���X�^�[�g
    if (waveTimer_ <= 0) {
        SpawnWave(); // �E�F�[�u���X�|�[��������
        waveCount_++; // �E�F�[�u�J�E���g�𑝂₷
        waveTimer_ = 300; // �^�C�}�[�����Z�b�g

        // �ő�E�F�[�u���ɒB�����珈�����I��
        if (waveCount_ >= maxWaves_) {
            // ��������̏���
            return;
        }
    }
}
