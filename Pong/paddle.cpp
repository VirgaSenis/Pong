#pragma once
#include "stdafx.h"
#include "paddle.h"



Paddle::Paddle(int width, int height, int initX, int initY) 
	: width(width)
	, height(height)
	, targetY(initY)
	, image( sf::RectangleShape( sf::Vector2f(width, height) ) )
{
	image.setPosition(initX, initY);
	image.setOrigin(width / 2, height / 2);
}

void Paddle::setPosition(int x, int y) {
	targetX = x;
	targetY = y;
	image.setPosition(x, y);
}

void Paddle::setTargetY(int y) {
	targetY = y;
}

float Paddle::getY() {
	return image.getPosition().y;
}

float Paddle::getTopY() {
	return image.getPosition().y - (height / 2);
}

float Paddle::getBottomY() {
	return image.getPosition().y + (height / 2);
}

float Paddle::getLeftX() {
	return image.getPosition().x - (width / 2);
}

float Paddle::getRightX() {
	return image.getPosition().x + (width / 2);
}

int Paddle::getWidth() {
	return width;
}

int Paddle::getHeight() {
	return height;
}

sf::RectangleShape Paddle::getImage() {
	return image;
}

void Paddle::move() {
	image.move(0, targetY - image.getPosition().y );
}

void Paddle::addTargetY(float y) {
	this->targetY += y;
}