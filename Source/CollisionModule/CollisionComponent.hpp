#pragma once

#include "CollisionRectangle.hpp"

class CollisionComponent : public CollisionRectangle {

public:
	CollisionComponent() :CollisionRectangle() {};
	CollisionComponent(const sf::Vector2f& position, const sf::Vector2f& size) :CollisionRectangle(position, size){};

	//event handlers
    void BeginOverlapHandler(void*) override;

	void EndOverlapHandler(void*) override;
};