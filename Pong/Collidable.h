#pragma once
#include <SFML/Graphics.hpp>

class Collidable {
public:
	bool intersects(sf::Vector2f);

protected:
	virtual float getTopY() = 0;
	virtual float getBottomY() = 0;
	virtual float getLeftX() = 0;
	virtual float getRightX() = 0;
};