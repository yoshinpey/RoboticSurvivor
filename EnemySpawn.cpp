#include "EnemySpawn.h"
#include <random>

#include "Player.h"
#include "EnemyManager.h"

// �R���X�g���N�^�̎���
EnemySpawn::EnemySpawn(EnemyManager* enemyManager, Player* player, int waveTimer, int maxWaves)
    : enemyManager_(enemyManager), player_(player), waveTimer_(waveTimer), waveCount_(0), maxWaves_(maxWaves) {}

// �E�F�[�u�̃X�|�[�������̎���
void EnemySpawn::SpawnWave() {

}

// �E�F�[�u�̍X�V�����̎���
void EnemySpawn::UpdateWave() 
{
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
