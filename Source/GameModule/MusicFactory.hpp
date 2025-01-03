#pragma once
#include <unordered_map>
#include <iostream>

enum class AllMusic
{
	Background, Title, GameOver, Stage, BoosterBackground
};

enum class AllSounds
{
	Bomb, Booster, Gate, Move1, Move2, PlantBomb, PlayersDeath, AllEnemiesDead, Miss
};

namespace MusicFactory
{
    void loadAllMusic(const std::string& path);

    void loadAllSounds(const std::string& path);
};