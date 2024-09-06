#pragma once

class Gun;

namespace GameManager
{

    void Initialize();
    void Update();
    void Draw();
    void Release();

    void SetGun(Gun* gun);
    Gun* GetGun();
};
