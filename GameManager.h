#pragma once

class GameObject;
class EnemyManager;

namespace GameManager
{
    void Initialize(GameObject* gameObject);
    void Update();
    void Release();

    GameObject* GetGameObject();
    EnemyManager* GetEnemyManager();
};
