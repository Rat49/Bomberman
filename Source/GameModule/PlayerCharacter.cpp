#include "PlayerCharacter.hpp"
#include "Common/Modules.hpp"
#include "InputModule/InputModule.hpp"
#include "Common/Logs.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <thread>
#include <chrono>

PlayerCharacter::PlayerCharacter()
{
	Modules::Input->LoadInputSettings("../../Data/Config/input_config.ini");
	Modules::Config->addFile("../../Data/Config/PlayerCharacterConfig.ini");
}

bool PlayerCharacter::init()
{
	const ConfigFile& playerConfig = Modules::Config->getFile("../../Data/Config/PlayerCharacterConfig.ini");
	speed = playerConfig.getSection("Player").getValue("speed").getFloat();

	playerMovement = Modules::Input->GetActionID("PlayerMovement");
	if (!playerMovement)
	{
		LOG("Failed to get PlayerMovement action ID.");
		return false;
	}

	playerMovementHandle = Modules::Input->RegisterEvent(playerMovement, std::bind(&PlayerCharacter::onMove, this, std::placeholders::_1));
	if (!playerMovementHandle)
	{
		LOG("Failed to register PlayerMovement event.");
		return false;
	}

	plantBomb = Modules::Input->GetActionID("PlantBomb");
	if (!plantBomb)
	{
		LOG("Failed to get PlantBomb action ID.");
		return false;
	}

	plantBombHandle = Modules::Input->RegisterEvent(plantBomb, [this](void* /*axis2DState*/) { this->onBombPlant(nullptr); });
	if (!plantBombHandle)
	{
		LOG("Failed to register PlantBomb event.");
		return false;
	}

	// Loading animations
	leftId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationLeft.ini");
	rightId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationRight.ini");
	upId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationUp.ini");
	downId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationDown.ini");

	if (leftId <= 0 || rightId <= 0 || upId <= 0 || downId <= 0)
	{
		LOG("Failed to load one or more animations.");
		return false;
	}

	currentAnimation = downId;

	if (const auto& animation = Modules::Sprite->getAnimation(downId))
	{
		animation->Play();
		updateAnimation(downId);
	}
	else
	{
		LOG("Failed to play initial animation.");
		return false;
	}

	return true;
}

void PlayerCharacter::onMove(void* axis2DState)
{
	sf::Vector2f state = *reinterpret_cast<sf::Vector2f*>(axis2DState);
	if(state.x == 1 && state.y == 0) { //RIGHT
		x+= velocity;
		updateAnimation(rightId);
	}
	else if (state.x == 0 && state.y == -1) { //DOWN
		y += velocity;
		updateAnimation(downId);
	}
	else if (state.x == -1 && state.y == 0) { //LEFT
		x -= velocity;
		updateAnimation(leftId);
	}
	else if (state.x == 0 && state.y == 1) { //UP 
		y -= velocity;
		updateAnimation(upId);
	}
}

void PlayerCharacter::onBombPlant(void* /*axis2DState*/)
{
	// Need to add and then get Player's position here
	bomb.Initialize(this->getCurrentPosition(), 1, 2.0f);
}

void PlayerCharacter::updateAnimation(int32_t id)
{
	m_isUpdated = true;
	if (auto animation = Modules::Sprite->getAnimation(id))
	{
		animation->setPosition(x, y);
		if (currentAnimation != id) {
			Modules::Sprite->getAnimation(currentAnimation)->Stop();

			animation->Play();
			currentAnimation = id;
		}
	}
}

std::shared_ptr<Animation> PlayerCharacter::getCurrentAnimation() const
{
	if (!m_isUpdated)
	{
		Modules::Sprite->getAnimation(currentAnimation)->Pause();
	}
	else {
		Modules::Sprite->getAnimation(currentAnimation)->Resume();
	}
	return Modules::Sprite->getAnimation(currentAnimation);
}

sf::Vector2f PlayerCharacter::getCurrentPosition() const
{
	return { x, y };
}

void PlayerCharacter::updateVelocity(float deltaTime)
{
	velocity = speed * deltaTime;
}

PlayerCharacter::~PlayerCharacter()
{
	Modules::Input->UnregisterEvent(playerMovement, playerMovementHandle);
	Modules::Input->UnregisterEvent(plantBombHandle, plantBombHandle);
}
