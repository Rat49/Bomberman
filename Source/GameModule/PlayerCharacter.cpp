#include "PlayerCharacter.hpp"
#include "Common/Modules.hpp"
#include "InputModule/InputModule.hpp"
#include "Common/Logs.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "GameModule/GameModule.hpp"
#include "Common/Directions.hpp"
#include <thread>
#include <chrono>

PlayerCharacter::PlayerCharacter()
{
	collision.setObjectParent(this);

    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties(getCurrentPosition(), sf::Vector2f(collisionBoxSize, collisionBoxSize));
}

bool PlayerCharacter::init()
{
    collisionBoxID = Modules::Physics->registerObject(collisionBox.get());
    Modules::Physics->addObject(collisionBox.get());

	//Modules::Input->LoadInputSettings("../../Data/Config/input_config.ini");
	Modules::Config->addFile("../../Data/Config/PlayerCharacterConfig.ini");

	const ConfigFile& playerConfig = Modules::Config->getFile("../../Data/Config/PlayerCharacterConfig.ini");
	speed = playerConfig.getSection("Player").getValue("speed").getFloat();
	maxBombs = playerConfig.getSection("PlayersBomb").getValue("maxBombs").getInt32();
    bombCapacity = playerConfig.getSection("BombUpBooster").getValue("bombCapacity").getInt32();
	bombDuration = playerConfig.getSection("BombsDuration").getValue("bombDuration").getFloat();

	activeBombs.reserve(maxBombs);

	playerMovement = Modules::Input->GetActionID("PlayerMovement");
	if (playerMovement < 0)
	{
		LOG("Failed to get PlayerMovement action ID.");
		return false;
	}

	playerMovementHandle = Modules::Input->RegisterEvent(playerMovement, std::bind(&PlayerCharacter::onMove, this, std::placeholders::_1));
	if (playerMovementHandle < 0)
	{
		LOG("Failed to register PlayerMovement event.");
		return false;
	}

	plantBomb = Modules::Input->GetActionID("PlantBomb");
	if (plantBomb < 0)
	{
		LOG("Failed to get PlantBomb action ID.");
		return false;
	}

	plantBombHandle = Modules::Input->RegisterEvent(plantBomb, [this](void* /*axis2DState*/) { this->onBombPlant(nullptr); });
	if (plantBombHandle < 0)
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
    collisionBox->setRectangleProperties(getCurrentPosition(), sf::Vector2f(collisionBoxSize, collisionBoxSize));

	if (!Modules::Game->getIsPaused())
    {
        sf::Vector2f state = *reinterpret_cast<sf::Vector2f*>(axis2DState);
        globalStats = state;

		if (state == rightDirection)
        { //RIGHT
            x += (canMoveRight ? velocity : 0.0f);
            updateAnimation(rightId);
        }
        else if (state == downDirection)
        { //DOWN
            y += (canMoveDown ? velocity : 0.0f);
            updateAnimation(rightId);
        }
        else if (state == leftDirection)
        { //LEFT
            x -= (canMoveLeft ? velocity : 0.0f);
            updateAnimation(rightId);
        }

        else if (state == upDirection)
        { //UP
            y -= (canMoveUp ? velocity : 0.0f);
            updateAnimation(rightId);
        }
    }
}

void PlayerCharacter::onCollision(CollisionComponent* other)
{
    if (other)
    {
        sf::Vector2f playerPos = getCurrentPosition();
        sf::Vector2f otherPos  = other->getRectangle().getPosition();
        canMoveRight = otherPos.x > playerPos.x && globalStats == rightDirection;
        canMoveDown            = globalStats == downDirection && otherPos.y > playerPos.y;
        canMoveLeft            = globalStats == leftDirection && otherPos.x < playerPos.x;
        canMoveUp              = globalStats == upDirection && otherPos.y < playerPos.y;

		if (!canMoveRight && !canMoveDown && !canMoveLeft && !canMoveUp)
        {
            canMoveRight = true;
            canMoveDown  = true;
            canMoveLeft  = true;
            canMoveUp    = true;
        }

        /*if (otherPos.x > playerPos.x && (globalStats == rightDirection))
        {
            canMoveRight = false;
            canMoveDown  = true;
            canMoveLeft  = true;
            canMoveUp    = true;
        }
        else if (otherPos.y > playerPos.y && (globalStats == downDirection))
        {
            canMoveDown = false;
            canMoveRight = true;
            canMoveLeft  = true;
            canMoveUp    = true;
        }
        else if (otherPos.x < playerPos.x && (globalStats == leftDirection))
        {
            canMoveLeft = false;
            canMoveRight = true;
            canMoveDown  = true;
            canMoveUp    = true;
        }
        else if (otherPos.y < playerPos.y && (globalStats == upDirection))
        {
            canMoveUp = false;
            canMoveRight = true;
            canMoveDown  = true;
            canMoveLeft  = true;
        }
       else
        {
            canMoveRight = true;
            canMoveDown  = true;
            canMoveLeft  = true;
            canMoveUp    = true;
		}*/
    }
}

void PlayerCharacter::onBombPlant(void* /*axis2DState*/)
{
	if (activeBombs.size() >= static_cast<size_t>(maxBombs))
	{
		LOG("Cannot plant more bombs. Maximum reached.");
		return;
	}

	// Need to add and then get Player's position here
	auto bomb = std::make_shared<Bomb>();
	bomb->Initialize(getCurrentPosition(), 1, bombDuration);
	activeBombs.push_back(bomb);
}

void PlayerCharacter::updateBombs(float deltaTime)
{
	for (auto it = activeBombs.begin(); it != activeBombs.end();)
	{
		auto& bomb = *it;
		bomb->update(deltaTime);

		if (bomb->hasExploded() && bomb->hasAnimExploded())
		{
			// Remove bomb if inactive
			it = activeBombs.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void PlayerCharacter::addMaxBombs()
{
    if (maxBombs<bombCapacity)
    {
        maxBombs++;
    }
}

void PlayerCharacter::drawBombs(sf::RenderWindow& window)
{
 	for (const auto& bomb : activeBombs)
	{
		//window.draw(*bomb->getCurrentAnimation());
		bomb->draw(window);
	}
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

void PlayerCharacter::PassThroughBombs(bool pass)
{
    canPassThroughBombs = pass;
}

void PlayerCharacter::updateVelocity(float deltaTime)
{
    velocity = speed * deltaTime;
}

void PlayerCharacter::updateSpeed(float factor)
{
    speed *= factor;
}

PlayerCharacter::~PlayerCharacter()
{
    Modules::Physics->unRegisterObject(collisionBoxID);

	Modules::Input->UnregisterEvent(playerMovement, playerMovementHandle);
	Modules::Input->UnregisterEvent(plantBombHandle, plantBombHandle);
}
