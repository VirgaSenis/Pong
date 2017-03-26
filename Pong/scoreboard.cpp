#pragma once

#include "stdafx.h"
#include "scoreboard.h"

Scoreboard::Scoreboard(sf::Font& font)
	: image(sf::Text("", font, 75))
{
	scores = new int[2]{0};
	image.setStyle(sf::Text::Bold);
	setString();
}

void Scoreboard::incrementScore(int player) {
	scores[player]++;
	setString();
}

void Scoreboard::setString() {
	image.setString(std::to_string(scores[COMPUTER]) + " : " + std::to_string(scores[USER]));
	sf::FloatRect rect = image.getLocalBounds();
	image.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
}

void Scoreboard::setPosition(int x, int y) {
	image.setPosition(x, y);
}

sf::Text Scoreboard::getImage() {
	return image;
}

int* Scoreboard::getScores() {
	return scores;
}