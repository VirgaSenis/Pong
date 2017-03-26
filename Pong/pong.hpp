#ifndef PONG_H
#define PONG_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <sstream>
#include <iostream>

bool isClicked(sf::Text bttn, sf::Vector2i pos);
void setTextOrig(sf::Text* text);

extern int windowWidth;
extern int windowHeight;
extern sf::Font font;

#endif