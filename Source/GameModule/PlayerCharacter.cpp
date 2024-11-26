#include "PlayerCharacter.hpp"
#include "Common/Modules.hpp"
#include "InputModule/InputModule.hpp"
#include "Common/Logs.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include <thread>
#include <chrono>

PlayerCharacter::PlayerCharacter()
{
	Modules::Input->LoadInputSettings("../../Data/Config/input_config.ini");
	playerMovement = Modules::Input->GetActionID("PlayerMovement");
	playerMovementHandle = Modules::Input->RegisterEvent(playerMovement, std::bind(&PlayerCharacter::onMove, this, std::placeholders::_1));

	plantBomb = Modules::Input->GetActionID("PlantBomb");
	plantBomb = Modules::Input->RegisterEvent(plantBomb, std::bind(&PlayerCharacter::onBombPlant, this, std::placeholders::_1));

	leftId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationLeft.ini");
	rightId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationRight.ini");
	upId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationUp.ini");
	downId = Modules::Sprite->createAnimation("../../Data/Config/PlayerAnimationDown.ini");

	currentAnimation = downId;

	if (const auto& animation = Modules::Sprite->getAnimation(downId))
	{
		animation->Play();
	}
}

void PlayerCharacter::onMove(void* axis2DState)
{
	sf::Vector2f state = *reinterpret_cast<sf::Vector2f*>(axis2DState);
	if(state.x == 1 && state.y == 0) { //RIGHT
		x++;
		updateAnimation(rightId);
	}
	else if (state.x == 0 && state.y == -1) { //DOWN
		y++;
		updateAnimation(downId);
	}
	else if (state.x == -1 && state.y == 0) { //LEFT
		x--;
		updateAnimation(leftId);
	}
	else if (state.x == 0 && state.y == 1) { //UP 
		y--;
		updateAnimation(upId);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void PlayerCharacter::onBombPlant(void* axis2DState)
{
	// Need to add and then get Player's position here
	//bomb.Initialize(this->getCurrentPosition(), 1, 2.0f);
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
	return Modules::Sprite->getAnimation(currentAnimation);
}
