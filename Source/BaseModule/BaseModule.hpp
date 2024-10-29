#pragma once
#include <SFML/Graphics.hpp>

class BaseModule {
public:

	virtual bool initialize() = 0;

	virtual void terminate() = 0;

	virtual void update(float deltaTime, sf::Window* window) = 0;
};