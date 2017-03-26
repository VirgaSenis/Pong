#pragma once
#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "Collidable.h"

#define PI 3.14159265

class Ball {
private:
	float x, y;
	int radius;
	int speed;
	float direction;
	int	lastCollision;

	sf::CircleShape image;

public:
	Ball(int, int, float);

	int getX();
	int getY();

	void setX(float);
	void setY(float);

	int getLastCollision();
	void setLastCollision(int);

	float getDirection();
	int getSpeed();

	sf::CircleShape getImage();
	void setPosition(float, float);
	void setDirection(float);

	bool isOutOfLeftBound();
	bool isOutOfRightBound(int);
	bool hasCollided(Collidable*);

	sf::Vector2f getLeftEdgeCoordinates();
	sf::Vector2f getRightEdgeCoordinates();
	sf::Vector2f getTopEdgeCoordinates();
	sf::Vector2f getBottomEdgeCoordinates();

	void move();
};

#endif
