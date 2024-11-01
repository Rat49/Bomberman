#pragma once

#include "CollisionRectangle.hpp"

class CollisionComponent : public CollisionRectangle {

public:
	CollisionComponent();
	CollisionComponent(const sf::Vector2f& position, const sf::Vector2f& size);
	
	~CollisionComponent();
	//event handlers
    void BeginOverlapHandler(void*) override;

	void EndOverlapHandler(void*) override;
private:
	int id;
};