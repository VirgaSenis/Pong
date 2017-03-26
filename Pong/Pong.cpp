// Pong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pong.hpp"
#include "menu.hpp"
#include "main.h"

int windowWidth;
int windowHeight;

sf::Font font;

int main(int argc, char** argv)
{

	windowWidth = 800;
	windowHeight = 600;

	font.loadFromFile("arial.ttf");

	//Applications variables
	//Window creation
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");

	//Mouse cursor no more visible
	//App.setMouseCursorVisible(false);

	//Main loop
	int returnCode = OPTION_MENU;
	while (returnCode != OPTION_EXIT)
	{
		switch (returnCode) {
		case OPTION_MENU :
			returnCode = start(window);
			break;
		case OPTION_PLAY :
			returnCode = play(window);
			break;
		}

	}

	window.close();
    return 0;
}

