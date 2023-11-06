#pragma once

class XP
{
public:
    XP();

    void Initialize();
    void AddExperience(int amount);
    void AddScore(int points);

    int GetExperience() const;
    int GetScore() const;

private:
    int experience;
    int score;
};
