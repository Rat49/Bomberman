#pragma once
#include <map>
#include "BaseModule/BaseModule.hpp"
#include "BoosterComponent.hpp"
#include "GameModule/PlayerCharacter.hpp"

class BoosterManager : public BaseModule
{
public:
	BoosterManager() = default;

	void addBooster(std::shared_ptr<BoosterComponent> newBooster);

	bool initialize(std::shared_ptr<PlayerCharacter> playerCharacter);

	void update(float deltaTime, sf::Window* window) override;

	void removeAllBoosters();

	void terminate() override;

private:
	std::map<int32_t, std::shared_ptr<BoosterComponent>> m_boosters;

	std::shared_ptr<PlayerCharacter> m_playerCharacter;
};

