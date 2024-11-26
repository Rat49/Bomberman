#pragma once
#include "InputModule/InputTypes.hpp"

class Animation;

class PlayerCharacter
{
public:
	PlayerCharacter();

	void onMove(void* axis2DState);

	void updateAnimation(int32_t id);

	std::shared_ptr<Animation> getCurrentAnimation() const;

	bool getIsUpdated() const { return m_isUpdated; }

	void setIsUpdated(bool isUpdated) { m_isUpdated = isUpdated; }

	sf::Vector2f getCurrentPosition() const;

	void updateVelocity(float deltaTime);

private:
	int32_t currentAnimation = -1;
	float x = 0.f;
	float y = 0.f;
	float speed = 0.f;
	float velocity = 0.f;

	ActionID playerMovement;
	FunctionHandle playerMovementHandle;
	int32_t leftId;
	int32_t rightId;
	int32_t upId;
	int32_t downId;

	bool m_isUpdated = true;
};