#include "XP.h"

XP::XP()
    : experience(0), score(0)
{
}

void XP::Initialize()
{
    // XPの初期化処理をここに記述
    experience = 0;
    score = 0;
}

void XP::AddExperience(int amount)
{
    experience += amount;
}

void XP::AddScore(int points)
{
    score += points;
}

int XP::GetExperience() const
{
    return experience;
}

int XP::GetScore() const
{
    return score;
}
