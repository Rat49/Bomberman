#pragma once

namespace sf {
	class Window;
}

class BaseModule {
public:

	virtual bool initialize() = 0;

	virtual void terminate() = 0;

	virtual void update(float deltaTime, sf::Window* window) = 0;
};