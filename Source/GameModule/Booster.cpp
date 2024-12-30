#include "GameModule/Booster.hpp"
#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "Boosters/SpeedBooster.hpp"
#include "Boosters/FireUpBooster.hpp"
#include "Boosters/BombUpBooster.hpp"
#include "Boosters/RemoteControlBooster.hpp"
#include "Boosters/InvincibleBooster.hpp"
#include "Boosters/PassBombBooster.hpp"
#include <iostream>
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

Booster::Booster(BoosterType type, float x, float y) : type(type)
{
    setPosition(x, y);

    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties((getPosition() + sf::Vector2f((gridSize - collisionBoxSize) / 2, (gridSize - collisionBoxSize) / 2)),
                                         sf::Vector2f(collisionBoxSize, collisionBoxSize));
}

// A function that returns the name of the booster type as a string
std::string Booster::getTypeAsString() const
{
    switch (type)
    {
        case BoosterType::Speed:
            return "SpeedUpBooster";
        case BoosterType::PassBomb:
            return "PassBombBooster";
        case BoosterType::FireUp:
            return "FireUpBooster";
        case BoosterType::BombUp:
            return "BombUpBooster";
        case BoosterType::RemoteControl:
            return "RemoteControlBooster";
        case BoosterType::InvincibleBooster:
            return "InvincibleBooster";
        case BoosterType::WallPass:
            return "WallPassBooster";
        case BoosterType::FlamePass:
            return "FlamePassBooster";
    }
    return "";
}

// This method is called when booster is picked up
std::shared_ptr<BoosterComponent> Booster::getBoosterComponent()
{
    isPickedUp = true;

    switch (type)
    {
        case BoosterType::Speed:
            return std::make_shared<SpeedBooster>();
        case BoosterType::PassBomb:
            return std::make_shared<PassBombBooster>();
        case BoosterType::FireUp:
            return std::make_shared<FireUpBooster>();
        case BoosterType::BombUp:
            return std::make_shared<BombUpBooster>();
        case BoosterType::RemoteControl:
            return std::make_shared<RemoteControlBooster>();
        case BoosterType::InvincibleBooster:
            return std::make_shared<InvincibleBooster>();
        case BoosterType::WallPass:
            return std::make_shared<SpeedBooster>();
        case BoosterType::FlamePass:
            return std::make_shared<SpeedBooster>();
    }
    return std::make_shared<SpeedBooster>();
}

void Booster::setCallbackID(EventID boosterPickupID)
{
	m_boosterPickupID = boosterPickupID;
}

void Booster::emitCallback() const
{
    Modules::Events->emit(m_boosterPickupID, nullptr);
}