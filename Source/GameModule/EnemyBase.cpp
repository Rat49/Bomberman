#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "GameModule/EnemyBase.hpp"
#include "SpriteModule/Animation.hpp"
#include "SpriteModule/Sprite.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include <random>
#include <set>
#include <utility>

EnemyType EnemyBase::getType() const
{
    return enemyType;
}

sf::Vector2f EnemyBase::getPosition() const
{
    return position;
}

std::shared_ptr<Animation> EnemyBase::getCurrentAnimation() const
{
    return Modules::Sprite->getAnimation(m_currentAnimationId);
}

void EnemyBase::initializeDeath()
{
    if (!isEnemyDead)
    {
        Modules::Sprite->getAnimation(m_currentAnimationId)->Stop();
        m_currentAnimationId = m_deatAnimationId;
        Modules::Sprite->getAnimation(m_currentAnimationId)->Play();
        Modules::Sprite->getAnimation(m_currentAnimationId)->setPosition(position);
        isEnemyDead = true;
    }
}

void EnemyBase::playLeftAnimation()
{

    if (!Modules::Sprite->getAnimation(m_deatAnimationId)->isPlaying())
    {
        Modules::Sprite->getAnimation(m_currentAnimationId)->Stop();
        m_currentAnimationId = m_leftAnimationId;
        Modules::Sprite->getAnimation(m_currentAnimationId)->Play();
        Modules::Sprite->getAnimation(m_currentAnimationId)->setPosition(position);
    }
}

void EnemyBase::playRightAnimation()
{
    if (!Modules::Sprite->getAnimation(m_deatAnimationId)->isPlaying())
    {
        Modules::Sprite->getAnimation(m_currentAnimationId)->Stop();
        m_currentAnimationId = m_rightAnimationId;
        Modules::Sprite->getAnimation(m_currentAnimationId)->Play();
        Modules::Sprite->getAnimation(m_currentAnimationId)->setPosition(position);
    }
}

bool EnemyBase::isDead() const
{
    if (!Modules::Sprite->getAnimation(m_currentAnimationId)->isPlaying() && isEnemyDead)
    {
        return true;
    }
    return false;
}

void EnemyBase::updateVelocity(float deltaTime)
{
    velocity = speed * deltaTime;
}