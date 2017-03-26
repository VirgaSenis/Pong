#include "stdafx.h"
#include "pong.hpp"

bool isClicked(sf::Text bttn, sf::Vector2i pos) {
	sf::FloatRect rect(bttn.getGlobalBounds());
	float left_x = rect.left;
	float right_x = rect.left + rect.width;
	float top_y = rect.top;
	float btm_y = rect.top + rect.height;
	return left_x <= pos.x && right_x >= pos.x && top_y <= pos.y && btm_y >= pos.y;
}

void setTextOrig(sf::Text* text) {
	sf::FloatRect rect = (*text).getLocalBounds();
	(*text).setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
}