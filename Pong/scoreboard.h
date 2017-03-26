#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define USER 0
#define COMPUTER 1

class Scoreboard {
private:
	int* scores;

	sf::Text image;

public:
	Scoreboard(sf::Font& font);
	void incrementScore(int);
	void setPosition(int, int);
	void setString();
	sf::Text getImage();
	int* getScores();
};

#endif