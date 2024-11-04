#include "AssetManagerTest.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include "Common/StringUtils.hpp"
#include <thread>
#include <chrono>

#include "AssetManager/PackageManager.hpp"

const std::string& AssetManagerTest::getName() const
{
	return Name;
}

void AssetManagerTest::setup()
{
	LOG("AssetManagerTest: setup()");
	Modules::Assets->initialize("../../Data/Config/assetmngr_config.ini");
	Modules::Assets->loadFont("Game/Fonts/arialbd.ttf");
}

void AssetManagerTest::run()
{
	LOG("AssetManagerTest: run()");
}

void AssetManagerTest::update(float, sf::RenderWindow* window)
{
	LOG("AssetManagerTest: update()");

	std::shared_ptr<sf::Font> font = Modules::Assets->getFont("Game/Fonts/arialbd.ttf");

	std::string message = "Loading font from asset manager...";
	sf::Text text;
	text.setFont(*font);
	text.setString(message);
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);

	sf::Vector2u windowSize  = window->getSize();
	sf::FloatRect textBounds = text.getGlobalBounds();
	float centerX            = (windowSize.x - textBounds.width) / 2;
	float centerY            = (windowSize.y - textBounds.height) / 2;
	text.setPosition(centerX, centerY);

	window->clear();
	window->draw(text); 
	window->display();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	PackageManager::createPackageFile("../../Assets");
}

bool AssetManagerTest::isComplete() const
{
	return true;
}