#include "RayCast.hpp"
#include "CollisionRectangle.hpp"

// Checks if ray intersects with rectangle
bool RayCast::rayIntersectsRectangle(const CollisionRectangle& rectangle, sf::Vector2f& endPoint) {
	sf::FloatRect bounds = rectangle.getRectangle().getGlobalBounds();


	// Horizontal Ray
	if (rayDirection.y == 0 && rayOrigin.y >= bounds.top && rayOrigin.y <= bounds.top + bounds.height) {
		if (rayDirection.x > 0 && rayOrigin.x <= bounds.left) { // Moving right
			endPoint = { bounds.left, rayOrigin.y };
			return true;
		}
		else if (rayDirection.x < 0 && rayOrigin.x >= bounds.left + bounds.width) { // Moving left
			endPoint = { bounds.left + bounds.width, rayOrigin.y };
			return true;
		}
	}
	// Vertical Ray
	else if (rayDirection.x == 0 && rayOrigin.x >= bounds.left && rayOrigin.x <= bounds.left + bounds.width) {
		if (rayDirection.y > 0 && rayOrigin.y <= bounds.top) { // Moving down
			endPoint = { rayOrigin.x, bounds.top };
			return true;
		}
		else if (rayDirection.y < 0 && rayOrigin.y >= bounds.top + bounds.height) { // Moving up
			endPoint = { rayOrigin.x, bounds.top + bounds.height };
			return true;
		}
	}

	return false;  // No intersection
}