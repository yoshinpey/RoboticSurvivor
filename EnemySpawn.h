#pragma once

#include "EnemyManager.h"
class Player;

class EnemySpawn 
{
private:
    EnemyManager* enemyManager_; // �G���Ǘ�����EnemyManager�ւ̃|�C���^
    Player* player_;             // �v���C���[�I�u�W�F�N�g�ւ̃|�C���^
    int waveTimer_;              // �E�F�[�u�̊Ԋu��\���^�C�}�[
    int waveCount_;              // ���݂̃E�F�[�u�J�E���g
    int maxWaves_;               // �ő�E�F�[�u��

public:
    // �R���X�g���N�^
    EnemySpawn(EnemyManager* enemyManager, Player* player, int waveTimer, int maxWaves);

    // �E�F�[�u�̃X�|�[������
    void SpawnWave();

    // �E�F�[�u�̍X�V����
    void UpdateWave();
};
