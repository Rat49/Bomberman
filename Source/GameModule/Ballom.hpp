#pragma once
#include "EnemyBase.hpp"

class LookLeftState;
class LookRightState;

class Ballom : public EnemyBase
{
public:
    Ballom() = default;

    void initialize(EnemyType type, sf::Vector2f spawnPosition) override;

private:
    std::shared_ptr<LookLeftState>  lookLeftState;
    std::shared_ptr<LookRightState> lookRightState;
};
