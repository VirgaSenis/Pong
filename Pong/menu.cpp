#include "stdafx.h"
#include "pong.hpp"
#include "menu.hpp"

using namespace std;

int gameLevel;

int start(sf::RenderWindow &window) {

	sf::Text title("Pong", font, 100);
	setTextOrig(&title);
	title.setStyle(sf::Text::Bold);
	title.setPosition(windowWidth * .5, windowHeight * .20);

	sf::Text difficulty("Difficulty: ", font, 50);
	setTextOrig(&difficulty);
	difficulty.setPosition(windowWidth*.45, windowHeight*.5);

	sf::Text easyButton("Easy", font);
	setTextOrig(&easyButton);
	easyButton.setPosition(windowWidth*.65, windowHeight*.5);

	sf::Text hardButton("Hard", font);
	setTextOrig(&hardButton);
	hardButton.setPosition(windowWidth*.65, windowHeight*.6);

	sf::Text exitButton("Exit Game", font);
	setTextOrig(&exitButton);
	exitButton.setPosition(windowWidth*.5, windowHeight*.8);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				exit(0);
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				if (isClicked(easyButton, mousePosition)) {
					gameLevel = 1;
					return OPTION_PLAY;
				}
				else if (isClicked(hardButton, mousePosition)) {
					gameLevel = 2;
					return OPTION_PLAY;
				}
				else if (isClicked(exitButton, mousePosition)) {
					return OPTION_EXIT;
				}
			}
		}

		window.clear();
		window.draw(easyButton);
		window.draw(hardButton);
		window.draw(exitButton);
		window.draw(title);
		window.draw(difficulty);
		window.display();
	}

	return 0;
}