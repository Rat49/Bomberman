#include "SpriteModule/Sprite.hpp"
#include <iostream>
#include <cstdint>

void Sprite::initialize(const std::string& name, const Atlas& atlas)
{
	auto textureRect = atlas.getTextureRect(name);

	if (textureRect)
	{
		setTexture(*atlas.getTexture());
		setTextureRect(*textureRect);
	}
}
