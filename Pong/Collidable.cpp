#include "stdafx.h"
#include "Collidable.h"

bool Collidable::intersects(sf::Vector2f coordinates) {
	float x = coordinates.x;
	float y = coordinates.y;

	return x >= getLeftX() && x <= getRightX() && y <= getBottomY() && y >= getTopY();
}