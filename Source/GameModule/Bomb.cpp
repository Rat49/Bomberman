#include "GameModule/Bomb.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "Common/Logs.hpp"
#include "GameModule/PlayerCharacter.hpp"
#include "GameModule/EnemyBase.hpp"
#include "UnbreakableObstacle.hpp"

Bomb::Bomb()
{
	collisionBox = std::make_unique<CollisionComponent>();

	collisionBox->setObjectParent(this);
}

bool Bomb::Initialize(const sf::Vector2f& newPosition, float newExplosionRadius, float newTimer)
{
	bombIdleID = Modules::Sprite->createAnimation("../../Data/Config/BombIdleAnimation.ini");
	bombUpID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionUpAnimation.ini");
	bombDownID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionDownAnimation.ini");
	bombLeftID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionLeftAnimation.ini");
	bombRightID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionRightAnimation.ini");
	bombCenterID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionCenterAnimation.ini");
    bombHorizontalID = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionHorizontallyAnimation.ini");
    bombVerticalID   = Modules::Sprite->createAnimation("../../Data/Config/BombExplosionVerticallyAnimation.ini");

	currentAnimation = bombIdleID;
	sf::Vector2f pos = alignToGrid(newPosition);

	if (const auto& animation = Modules::Sprite->getAnimation(bombIdleID))
	{
		getCurrentAnimation()->setPosition(pos);
		animation->Play();
	}
	else
	{
		LOG("Failed to retrieve animation with ID: " + std::to_string(bombIdleID));
	}

	if (newPosition.x < 2 || newPosition.y < 2)
	{
		LOG("Wrong position. The position of bomb on x and y must be greater than 2.");
		return false;
	}

	if (newExplosionRadius < 1)
	{
		LOG("Explosion Radius must be at least 1.");
		return false;
	}

	if (newTimer < 2.0f)
	{
		LOG("Timer must be at least 2.");
		return false;
	}

	this->position = pos;
	this->explosionRadius = newExplosionRadius;
	this->timer = newTimer;

	collisionBox->setRectangleProperties(position + sf::Vector2f((gridSize - collisionBoxSize) / 2,
                                                                 (gridSize - collisionBoxSize) / 2),
                                         sf::Vector2f(collisionBoxSize, collisionBoxSize));

	return true;
}

// Bomb update
void Bomb::update(float deltaTime, bool canDetonate)
{
	if (exploded)
	{
		explosionTimer -= deltaTime;
		if (explosionTimer <= 0.0f)
		{
			animExploded = true;
            isDetonating = false;
		}
        return;
	}
    // when player canDetonate (booster picked) and key for detonating isn't pressed previously -> timer should stay the same
    if (!canDetonate || isDetonating)
    {
        timer -= deltaTime;
    }

    if (timer < 0.0f)
    {
        Modules::Physics->deleteObject(collisionBox.get());
        explode();
    }
}

// Drawing a bomb
void Bomb::draw(sf::RenderWindow& window)
{
	if (!Modules::Sprite->getAnimation(bombIdleID)->isPlaying())
		exploded = true;

	if (canChangeObstacleAnim)
	{
		for (auto& [obstacle, pos] : obstaclesHit)
		{
			if (obstacle)
			{
				obstacle->changeAnim(pos);
			}
		}
		canChangeObstacleAnim = false;
	}

	// Draws a bomb if it hasn't exploded
	if (!exploded)
	{
		if (auto animation = Modules::Sprite->getAnimation(bombIdleID))
		{
			window.draw(*animation);
		}
	}
	// Draws an explosion
	else if(exploded)
	{

		sf::Vector2f directions[] =
		{
			// Right
			{1, 0},
			// Left
			{-1, 0},
			// Down
			{0, 1},
			// Up
			{0, -1}
		};
		
		sf::Vector2f animPos;

		for (const auto& direction : directions)
		{
            for (int i = 1; i <= explosionRadius; ++i)
            {
                sf::Vector2f offset = direction * (64.0f * i);
                sf::Vector2f animPoss = alignToGrid(position + offset);

                int32_t animationID;

                if (i < explosionRadius)
                {
                    // Use horizontal or vertical animations for segments
                    animationID = (direction.x != 0) ? bombHorizontalID : bombVerticalID;
                }
                else
                {
                    // Use end animations for the final segment
                    animationID = getExplosionAnimationID(direction);
                }

                if (auto animation = Modules::Sprite->getAnimation(animationID))
                {
                    animation->setPosition(animPoss);
                    window.draw(*animation);
                }
            }
        }

		// Draw the center of the explosion
		if (auto animation = Modules::Sprite->getAnimation(bombCenterID))
		{
			sf::Vector2f pos = alignToGrid(position);
			animation->setPosition(pos);
			window.draw(*animation);
		}
	}
}

std::shared_ptr<Animation> Bomb::getCurrentAnimation() const
{
	return Modules::Sprite->getAnimation(currentAnimation);
}

// Explosion activation
void Bomb::explode()
{

	auto animation = Modules::Sprite->getAnimation(bombIdleID);
	animation->Stop();

	int32_t animationID = getExplosionAnimationID(sf::Vector2f(-1, 0));
	currentAnimation = animationID;
	if (animation = Modules::Sprite->getAnimation(bombCenterID))
	{
		animation->setPosition(sf::Vector2f(64.0f, 64.0f));
		animation->Play();
	}

	sf::Vector2f directions[] =
	{
		// Right
		{1, 0},
		// Left
		{-1, 0},
		// Down
		{0, 1},
		// Up
		{0, -1}
	};

	for (const auto& direction : directions)
	{
        if (isDirectionSafe(position, direction, explosionRadius))
        {
            explosionEffect(direction);

            for (int i = 1; i <= explosionRadius; ++i)
            {
                sf::Vector2f offset  = direction * (64.0f * i);
                sf::Vector2f animPos = alignToGrid(position + offset);

                int32_t animationIDs;

                if (i < explosionRadius)
                {
                    // Use horizontal or vertical animations for segments
                    animationIDs = (direction.x != 0) ? bombHorizontalID : bombVerticalID;
                }
                else
                {
                    // Use end animations for the final segment
                    animationIDs = getExplosionAnimationID(direction);
                }

                if (auto animationn = Modules::Sprite->getAnimation(animationIDs))
                {
                    animationn->setPosition(animPos);
                    animationn->Play();
                }
            }
        }
    }
}

void Bomb::setTimer(int32_t inc)
{
    timer = inc * detonateCooldown;
	isDetonating = true;
}

// Method about what will happen when there is an explosion
void Bomb::explosionEffect(const sf::Vector2f& direction)
{
    sf::Vector2f endPoint;

    sf::Vector2f newDirection = directionToPosition(direction);
    sf::Vector2f alignPos = alignToGrid(position);
    sf::Vector2f directionAndPosition = alignPos + newDirection;

    hitResult = std::make_pair(Modules::Physics->rayCast(sf::Vector2f(alignPos.x+32.f, alignPos.y+32.f), newDirection, explosionRadius, endPoint), directionAndPosition);

    if (hitResult.first)
    {
        if (auto* hitObstacle = dynamic_cast<Obstacle*>(hitResult.first->getObjectParent()))
        {
            canChangeObstacleAnim = true;
            obstaclesHit.push_back(std::make_pair(hitObstacle, directionAndPosition));
            hitObstacle->initializeDestruction();
        }
        else if (auto* hitPlayer = dynamic_cast<PlayerCharacter*>(hitResult.first->getObjectParent()))
        {
            hitPlayer->die();
        }
        else if (auto* hitEnemy = dynamic_cast<EnemyBase*>(hitResult.first->getObjectParent()))
        {
            hitEnemy->initializeDeath();
        }
    }

    // Activation of direction animation
    int32_t animationID = getExplosionAnimationID(direction);
    currentAnimation    = animationID;
    if (auto animation = Modules::Sprite->getAnimation(animationID))
    {
        animation->setPosition(directionAndPosition);
        animation->Play();
    }


}

int32_t Bomb::getExplosionAnimationID(const sf::Vector2f& direction) const
{
	if (direction == sf::Vector2f{ 1, 0 }) return bombRightID; // Right
	if (direction == sf::Vector2f{ -1, 0 }) return bombLeftID; // Left
	if (direction == sf::Vector2f{ 0, 1 }) return bombDownID; // Down
	if (direction == sf::Vector2f{ 0, -1 }) return bombUpID;  // Up
	if (direction == sf::Vector2f{ 0, 0 }) return bombCenterID;  // Center

	return 0;
}

sf::Vector2f Bomb::directionToPosition(sf::Vector2f newDirection)
{
	sf::Vector2f dir = sf::Vector2f(newDirection.x * 64.0f, newDirection.y * 64.0f);

	return dir;
}

bool Bomb::isDirectionSafe(const sf::Vector2f& origin, const sf::Vector2f& direction, float maxDistance)
{
    sf::Vector2f endPoint;
    sf::Vector2f newDirection = directionToPosition(direction);
    auto hitObject = Modules::Physics->rayCast(origin, newDirection, maxDistance, endPoint);

    if (hitObject)
    {
        auto* obstacle = dynamic_cast<UnbreakableObstacle*>(hitObject->getObjectParent());
        if (obstacle)
        {
            //direction is blocked
            return false; 
        }
    }

	//direction is safe
    return true; 
}

sf::Vector2f Bomb::alignToGrid(const sf::Vector2f& newPosition)
{
    float alignedX = std::round(newPosition.x / gridSize) * gridSize;
    float alignedY = std::round(newPosition.y / gridSize) * gridSize;
	return { alignedX, alignedY };
}

Bomb::~Bomb() {
}
