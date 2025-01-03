#pragma once

#include <memory>
#include <vector>

class Obstacle;
class Gate;
class Booster;
class UnbreakableObstacle;
class EnemyBase;

enum class GameLevelType
{
    Easy   = 1,
    Medium = 2,
    Hard   = 3
};

struct LevelConfigs
{
    GameLevelType levelType;
    int32_t       enemyCount;
    int32_t       breakableCount;
    int32_t       boostersCount;
};

struct GeneratedElements
{
    std::vector<std::shared_ptr<UnbreakableObstacle>> unbreakableObstacles;
    std::vector<std::shared_ptr<Booster>>             boosters;
    std::vector<std::shared_ptr<EnemyBase>>           enemies;
    std::vector<std::shared_ptr<Obstacle>>            obstacles;
    std::vector<std::shared_ptr<Gate>>                gates;
    std::shared_ptr<std::vector<std::vector<bool>>>   navGrid;
};
