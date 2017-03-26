#pragma once
#ifndef WALL_H
#define WALL_H

#include "Collidable.h"

class Wall : public Collidable {
private :
	int width, height;
	sf::RectangleShape image;

public :
	Wall(int, int, float, float);
	sf::RectangleShape getImage();

	float getTopY();
	float getBottomY();
	float getLeftX();
	float getRightX();
};

#endif // !WALL_H
