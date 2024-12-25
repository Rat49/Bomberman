#pragma once
#include "EnemyBase.hpp"
#include "NavigationModule/Navigation.hpp"
#include "NavigationModule/Algorithm.hpp"

class FollowState;
class StandbyState;

class Dahl : public EnemyBase
{
public:
    Dahl() = default;

    void initialize(EnemyType type, sf::Vector2f spawnPosition) override;

    void initialzieNavModule(std::shared_ptr<std::vector<std::vector<bool>>> aiGrid);

    std::unique_ptr<NavigationModule> m_navModule;

private:
    std::shared_ptr<FollowState> m_folowState;
    std::shared_ptr<StandbyState> m_standbyState;

};
