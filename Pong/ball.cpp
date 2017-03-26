#include "stdafx.h"
#include "ball.h"

Ball::Ball(int radius, int speed, float direction) 
	: radius(radius)
	, speed(speed)
	, direction(direction)
	, image(sf::CircleShape(radius)) 
	{
		image.setOrigin(radius, radius);
		lastCollision = -1;
	}

sf::CircleShape Ball::getImage() {
	return image;
}

void Ball::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
	image.setPosition(x, y);
}

int Ball::getLastCollision() {
	return lastCollision;
}

void Ball::setLastCollision(int collision) {
	lastCollision = collision;
}

int Ball::getX() {
	return x;
}

int Ball::getY() {
	return y;
}

void Ball::setX(float x) {
	this->x = x;
	image.setPosition(x, y);
}

void Ball::setY(float y) {
	this->y = y;
	image.setPosition(x, y);
}


sf::Vector2f Ball::getLeftEdgeCoordinates() {
	return sf::Vector2f(x - radius, y);
}

sf::Vector2f Ball::getRightEdgeCoordinates() {
	return sf::Vector2f(x + radius, y);
}

sf::Vector2f Ball::getTopEdgeCoordinates() {
	return sf::Vector2f(x, y - radius);
}
sf::Vector2f Ball::getBottomEdgeCoordinates() {
	return sf::Vector2f(x, y + radius);
}

float Ball::getDirection() {
	return direction;
}

void Ball::setDirection(float direction) {
	this->direction = direction;
}

bool Ball::isOutOfLeftBound() {
	return x < -radius;
}

bool Ball::isOutOfRightBound(int boundX) {
	return x > boundX + radius;
}

bool Ball::hasCollided(Collidable* obj) {
	return obj->intersects(getLeftEdgeCoordinates()) || obj->intersects(getRightEdgeCoordinates())
		|| obj->intersects(getTopEdgeCoordinates()) || obj->intersects(getBottomEdgeCoordinates());
}

void Ball::move() {
	float offsetX = speed * sin(direction*PI / 180);
	float offsetY = speed * -cos(direction*PI / 180);

	image.move(offsetX, offsetY);

	sf::Vector2f newPosition = image.getPosition();
	this->x = newPosition.x;
	this->y = newPosition.y;
}

int Ball::getSpeed() {
	return speed;
}