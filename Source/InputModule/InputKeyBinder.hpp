#pragma once
#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"

class InputKeyBinder
{
public:
	InputKeyBinder();

	sf::Keyboard::Key GetButton(const std::string& buttonString) const;

private:
	std::unordered_map<std::string, sf::Keyboard::Key> keyMap;
};

