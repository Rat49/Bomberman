#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <unordered_map>

class InputKeyBinder
{
public:
    InputKeyBinder();

    sf::Keyboard::Key GetButton(const std::string& buttonString) const;

private:
    std::unordered_map<std::string, sf::Keyboard::Key> keyMap;
};
