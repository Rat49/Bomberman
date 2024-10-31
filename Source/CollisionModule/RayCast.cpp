#include "RayCast.hpp"
#include "CollisionRectangle.hpp"

// Checks if ray intersects with rectangle
bool RayCast::rayIntersectsRectangle(const CollisionRectangle& rectangle, sf::Vector2f& endPoint) {
	sf::FloatRect bounds = rectangle.getRectangle().getGlobalBounds();

	sf::Vector2f temporary;
	// Horizontal Ray
	if (rayDirection.x != 0) {
		float tx1 = (bounds.left - rayOrigin.x) / rayDirection.x;
		float tx2 = (bounds.left + bounds.width - rayOrigin.x) / rayDirection.x;

		float t = std::min(tx1, tx2);
		if (t >= 0 && t <= rayMaxDistance) {
			temporary = rayOrigin + rayDirection * t;
			if (temporary.y >= bounds.top && temporary.y <= bounds.top + bounds.height) {
				endPoint = temporary;
				return true;
			}
		}
	}

	if (rayDirection.y != 0) {
		float ty1 = (bounds.top - rayOrigin.y) / rayDirection.y;
		float ty2 = (bounds.top + bounds.height - rayOrigin.y) / rayDirection.y;

		float t = std::min(ty1, ty2);
		if (t >= 0 && t <= rayMaxDistance) {
			temporary = rayOrigin + rayDirection * t;
			if (temporary.x >= bounds.left && temporary.x <= bounds.left + bounds.width) {
				endPoint = temporary;
				return true;
			}
		}
	}

	return false;  // No intersection
}