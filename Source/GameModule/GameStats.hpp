#pragma once
#include "EventSystem/EventTypes.hpp"
#include "LevelHandlingModule/Level.hpp"
#include <memory>

class GameStats
{
public:
    GameStats() = default;

    void initialize(std::shared_ptr<Level> levelController);

    void terminate() const;

    void onEnemieDeath();

    void onBoosterCollected();

    void onObstacleDestroyed();

    int32_t getPoints() const
    {
        return m_points;
    }

    void resetPoints()
    {
        m_points = 0;
    } // reset when player looses all of the lives

    void levelChange(int32_t time); // updates callbacks and applies remaining time  score += m_time

private:
    int32_t m_points = 0;

    int32_t m_enemieKillPoints = 0;

    int32_t m_obstacleDestructionPoints = 0;

    int32_t m_boosterCollectPoints = 0;

    EventID m_enemieDeathID = -1;

    EventID m_obstacleDestructionID = -1;

    EventID m_boosterCollectID = -1;

    FunctionHandle m_enemieDeathHandle = -1;

    FunctionHandle m_obstacleDestructionHandle = -1;

    FunctionHandle m_boosterCollectHandle = -1;

    std::shared_ptr<Level> m_level;
};
