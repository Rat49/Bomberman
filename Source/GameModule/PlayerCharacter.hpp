#pragma once
#include "InputModule/InputTypes.hpp"
#include "GameModule/Bomb.hpp"

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

private:
	int32_t currentAnimation = -1;
	float x = 0.f;
	float y = 0.f;

	ActionID playerMovement;
	FunctionHandle playerMovementHandle;
	ActionID plantBomb;
	FunctionHandle plantBombHandle;
	int32_t leftId;
	int32_t rightId;
	int32_t upId;
	int32_t downId;

	Bomb bomb;

	bool m_isUpdated = true;
};