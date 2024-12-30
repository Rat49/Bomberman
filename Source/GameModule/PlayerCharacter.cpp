#include "PlayerCharacter.hpp"
#include "Common/Modules.hpp"
#include "InputModule/InputModule.hpp"
#include "Common/Logs.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "GameModule/GameModule.hpp"
#include "Common/Directions.hpp"
#include "Booster.hpp"
#include <thread>
#include <chrono>

PlayerCharacter::PlayerCharacter()
{
    collisionBox = std::make_unique<PlayerCollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties((getCurrentPosition() + sf::Vector2f(0.f, (gridSize - collisionBoxSize) / 2)),
                                         sf::Vector2f(collisionBoxSize, collisionBoxSize));
}
bool PlayerCharacter::init()
{

	//Modules::Input->LoadInputSettings("../../Data/Config/input_config.ini");
	Modules::Config->addFile("../../Data/Config/PlayerCharacterConfig.ini");

	const ConfigFile& playerConfig = Modules::Config->getFile("../../Data/Config/PlayerCharacterConfig.ini");
	speed = playerConfig.getSection("Player").getValue("speed").getFloat();
	maxBombs = playerConfig.getSection("PlayersBomb").getValue("maxBombs").getInt32();
    bombCapacity = playerConfig.getSection("BombUpBooster").getValue("bombCapacity").getInt32();
	bombDuration = playerConfig.getSection("BombsDuration").getValue("bombDuration").getFloat();
    invincibilityDuration = playerConfig.getSection("InvincibeBooster").getValue("invincibilityDuration").getFloat();
    currentExposionRadius = playerConfig.getSection("ExplosionRadius").getValue("explosionRadius").getFloat();
    maxExposionRadius = playerConfig.getSection("MaxExplosionRadius").getValue("maxExplosionRadius").getFloat();

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

	plantBombHandle = Modules::Input->RegisterEvent(plantBomb, std::bind(&PlayerCharacter::onBombPlant, this, std::placeholders::_1));
	if (plantBombHandle < 0)
	{
		LOG("Failed to register PlantBomb event.");
		return false;
	}

	detonateBomb = Modules::Input->GetActionID("DetonateBomb");
    if (detonateBomb < 0)
    {
        LOG("Failed to get DetonateBomb action ID.");
        return false;
    }

    detonateBombHandle = Modules::Input->RegisterEvent(detonateBomb, std::bind(&PlayerCharacter::onBombDetonate, this, std::placeholders::_1));
    if (plantBombHandle < 0)
    {
        LOG("Failed to register DetonateBomb event.");
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

	if (!Modules::Game->getIsPaused())
    {
        sf::Vector2f state = *reinterpret_cast<sf::Vector2f*>(axis2DState);
        currentDirection   = state;
		if (state == rightDirection)
        { //RIGHT
            x += velocity;
            updateAnimation(rightId);
        }
        else if (state == downDirection)
        { //DOWN
            y += velocity;
            updateAnimation(downId);
        }
        else if (state == leftDirection)
        { //LEFT
            x -= velocity;
            updateAnimation(leftId);
        }

        else if (state == upDirection)
        { //UP
            y -= velocity;
            updateAnimation(upId);
        }
        collisionBox->setRectangleProperties(getCurrentPosition() + sf::Vector2f(0.f, (gridSize - collisionBoxSize) / 2),
                                             sf::Vector2f(collisionBoxSize, collisionBoxSize));

        Modules::Physics->updateCollision();
    }
}

void PlayerCharacter::handleEnemyOverlap(EnemyBase* )
{
	// loose life...
}

void PlayerCharacter::handleObstacleOverlap(bool)
{
    if (currentDirection == rightDirection)
    { //RIGHT
        x -= velocity;
    }
    else if (currentDirection == downDirection)
    { //DOWN
        y -= velocity;
    }
    else if (currentDirection == leftDirection)
    { //LEFT
        x += velocity;
    }
    else if (currentDirection == upDirection)
    { //UP
        y += velocity;
    }
    collisionBox->setRectangleProperties(getCurrentPosition() + sf::Vector2f(0.f, (gridSize - collisionBoxSize) / 2),
                                         sf::Vector2f(collisionBoxSize, collisionBoxSize));
}

void PlayerCharacter::handleBoosterOverlap(Booster* booster)
{
    LOG("Picked up: $", booster->getTypeAsString());
    Modules::Game->addBooster(booster->getBoosterComponent());
}

void PlayerCharacter::onBombPlant(void* state)
{
    bool isPressed = *reinterpret_cast<bool*>(state);

	if (isPressed)
    {
        if (activeBombs.size() >= static_cast<size_t>(maxBombs))
        {
            LOG("Cannot plant more bombs. Maximum reached.");
            return;
        }

        // Need to add and then get Player's position here
        auto bomb = std::make_shared<Bomb>();
        bomb->Initialize(getCurrentPosition(), currentExposionRadius, bombDuration);
        activeBombs.push_back(bomb);
    }
}

void PlayerCharacter::onBombDetonate(void*)
{
    if (activeBombs.size() > 0 && !isDetonating && canDetonate)
    {
        isDetonating = true;

        bombsToDetonate = static_cast<int32_t>(activeBombs.size());
        for (int32_t i = 0; i < bombsToDetonate; i++)
        {
            activeBombs[i]->setTimer(i);
        }
	}
}

void PlayerCharacter::updateBombs(float deltaTime)
{
	for (auto it = activeBombs.begin(); it != activeBombs.end();)
	{
		auto& bomb = *it;
        bomb->update(deltaTime, canDetonate);

		if (bomb->hasExploded() && bomb->hasAnimExploded())
        {
            // Remove bomb if inactive
            it = activeBombs.erase(it);
            if (isDetonating)
            {
                --bombsToDetonate;
                if (bombsToDetonate == 0)
                {
                    isDetonating = false;
                }
            }
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
void PlayerCharacter::addExplosionRadius()
{
    if (currentExposionRadius < maxExposionRadius)
    {
        currentExposionRadius++;
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
	return { x , y };
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
    LOG("Speed: $", speed);
}

PlayerCharacter::~PlayerCharacter()
{
    Modules::Physics->unRegisterObject(collisionBoxID);

	Modules::Input->UnregisterEvent(playerMovement, playerMovementHandle);
	Modules::Input->UnregisterEvent(plantBombHandle, plantBombHandle);
}

void PlayerCharacter::startInvincibility()
{
	isInvincible = true;
	invincibilityStartTime = std::chrono::high_resolution_clock::now();
}

void PlayerCharacter::updateInvincibility()
{
	if (isInvincible)
	{
		auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<float>(invincibilityDuration);

        if (now - invincibilityStartTime >= duration)
        {
            isInvincible = false;
        }
	}
}

bool PlayerCharacter::getIsInvincible() const
{
	return isInvincible;
}

// TODO
// To check collision with player use this to avoid booster effect if booster effect is active:
// if (!player.getIsInvincible())
// {
//		Handle damage from bombs or enemies
// }