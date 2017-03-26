#include "stdafx.h"
#include "Wall.h"

Wall::Wall(int width, int height, float x, float y)
	: width(width)
	, height(height)
	, image(sf::Vector2f(width, height)) 
{
	image.setOrigin(width / 2, height / 2);
	image.setPosition(x, y);
}

float Wall::getTopY() {
	return image.getPosition().y - (height / 2);
}

float Wall::getBottomY() {
	return image.getPosition().y + (height / 2);
}

float Wall::getLeftX() {
	return image.getPosition().x - (width / 2);
}

float Wall::getRightX() {
	return image.getPosition().x + (width / 2);
}

sf::RectangleShape Wall::getImage() {
	return image;
}