#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include "Collidable.h"

class Paddle : public Collidable {
private:
	float targetX, targetY;
	int width, height;
	sf::RectangleShape image;


public:
	Paddle(int, int, int, int);

	float getTopY();
	float getBottomY();
	float getLeftX();
	float getRightX();

	float getY();
	void setPosition(int, int);
	void setTargetY(int);
	void addTargetY(float);
	int getWidth();
	int getHeight();

	sf::RectangleShape getImage();

	void move();
};

#endif // ! PADDLE_H

