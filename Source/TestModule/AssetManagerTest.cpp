#include "AssetManagerTest.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include "SpriteModule/Sprite.hpp"
#include <thread>
#include <chrono>

#include <fstream>

const std::string& AssetManagerTest::getName() const
{
	return Name;
}

void AssetManagerTest::setup()
{
	LOG("AssetManagerTest: setup()");
}

void AssetManagerTest::run()
{
	LOG("AssetManagerTest: run()");
}

void AssetManagerTest::update(float, sf::RenderWindow* window)
{
	LOG("AssetManagerTest: update()");

	std::shared_ptr<sf::Font> font       = Modules::Assets->getFont("Game/Fonts/arial.ttf");
	std::shared_ptr<sf::Texture> texture = Modules::Assets->getTexture("Game/Docs/logo.jpg");
	
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

	Sprite sprite;
	sprite.setTexture(*texture);

	sf::FloatRect spriteBounds = sprite.getLocalBounds();
	sprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
	sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	float scaleX = (float)(windowSize.x) / sprite.getLocalBounds().width;
	float scaleY = (float)(windowSize.y / 2) / sprite.getLocalBounds().height;
	sprite.setScale(scaleX, scaleY);

	window->clear();
	window->draw(text); 
	window->display();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	window->clear();
	window->draw(sprite);
	window->display();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

bool AssetManagerTest::isComplete() const
{
	return true;
}