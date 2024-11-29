#include "BoosterManagerTest.hpp"
#include "Common/Logs.hpp"
#include "BoosterManager/BoosterManager.hpp"
#include "BoosterManager/BoosterComponent.hpp"

class DummyBooster : public BoosterComponent
{
public:
	DummyBooster()
	{
		m_boosterID = 0;
		m_shouldRemoveEffect = false;
	}

	bool initialize()
	{
		m_boosterID = 1;
		return true;
	}

	virtual int32_t getBoosterID()
	{
		return m_boosterID;
	}

	virtual void applyEffect(PlayerCharacter&) 
	{
		LOG("Effect applied to the player");
	}

	// If it returns true, the booster's effect will be removed once.
	// If it returns false, the booster's effect will be gradually removed over multiple events until certain condition is achieved
	virtual bool removeEffect(PlayerCharacter&)
	{
		LOG("Effect removed from the player");
		return true;
	}

	virtual bool shoulRemoveEffect()
	{
		m_shouldRemoveEffect = true;
		return m_shouldRemoveEffect;
	}
private:
	int32_t m_boosterID;
	bool m_shouldRemoveEffect;
};

const std::string& BoosterManagerTest::getName() const
{
	return m_name;
}

void BoosterManagerTest::setup()
{
	LOG("$ setup", m_name);
	DummyBooster db;
	db.initialize();
	Modules::BoostersManager->addBooster(std::make_shared<DummyBooster>(db));
	Modules::BoostersManager->addBooster(std::make_shared<DummyBooster>(db));
	Modules::BoostersManager->addBooster(std::make_shared<DummyBooster>(db));
}

void BoosterManagerTest::run()
{
	LOG("$ run", m_name);
}

void BoosterManagerTest::update(float, sf::RenderWindow*)
{
	LOG("$ update", m_name);
}

bool BoosterManagerTest::isComplete() const
{
	Modules::BoostersManager->removeAllBoosters();
	return true;
}