#pragma once
#include "InputModule/InputTypes.hpp"
#include "GameModule/Bomb.hpp"
#include <chrono>

class Animation;

class PlayerCharacter
{
public:
	PlayerCharacter();

	~PlayerCharacter();

	bool init();

	void onMove(void* axis2DState);

	void onBombPlant(void* axis2DState);

	void updateAnimation(int32_t id);

	std::shared_ptr<Animation> getCurrentAnimation() const;

	bool getIsUpdated() const { return m_isUpdated; }

	void setIsUpdated(bool isUpdated) { m_isUpdated = isUpdated; }

	sf::Vector2f getCurrentPosition() const;

	void updateVelocity(float deltaTime);

	void updateBombs(float deltaTime);

	void drawBombs(sf::RenderWindow& window);

	void startInvincibility();

	void updateInvincibility();

	bool getIsInvincible() const;

private:
	int32_t currentAnimation = -1;
	float x = 70.f;
	float y = 70.f;
	float speed = 0.f;
	int32_t maxBombs;
	float velocity = 0.f;

	ActionID playerMovement;
	FunctionHandle playerMovementHandle;
	ActionID plantBomb;
	FunctionHandle plantBombHandle;
	int32_t leftId;
	int32_t rightId;
	int32_t upId;
	int32_t downId;

	std::vector<std::shared_ptr<Bomb>> activeBombs;

	bool m_isUpdated = true;

	bool isInvincible = false;
	std::chrono::time_point<std::chrono::high_resolution_clock> invincibilityStartTime;
    float invincibilityDuration;
};