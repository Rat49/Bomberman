#pragma once

namespace sf {
	class Window;
}

class BaseModule {
public:

	virtual bool initialize() { return true; }

	virtual void terminate() = 0;

	virtual void update(float, sf::Window*) {}
};