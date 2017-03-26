#include "stdafx.h"
#include "pong.hpp"
#include "menu.hpp"
#include "ball.h"
#include "paddle.h"
#include "Wall.h"
#include "scoreboard.h"
#include <SFML/Audio.hpp>

using namespace std;

#define MAX_SCORE 10

int end(sf::RenderWindow& window, char* endText) {
	window.setMouseCursorVisible(true);

	sf::Text mainText(endText, font, 75);
	setTextOrig(&mainText);
	mainText.setPosition(windowWidth * .5, windowHeight * .3);

	sf::Text playAgainButton("Play Again", font);
	setTextOrig(&playAgainButton);
	playAgainButton.setPosition(windowWidth * .5, windowHeight * .5);

	sf::Text mainMenuButton("Main Menu", font);
	setTextOrig(&mainMenuButton);
	mainMenuButton.setPosition(windowWidth * .5, windowHeight * .6);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				
				if (isClicked(playAgainButton, mousePosition)) {
					return OPTION_PLAY;
				}
				else if (isClicked(mainMenuButton, mousePosition)) {
					return OPTION_MENU;
				}
			}

			else if (event.type == sf::Event::Closed) {
				window.close();
				exit(0);
			}

		}

		window.clear();
		window.draw(mainText);
		window.draw(playAgainButton);
		window.draw(mainMenuButton);
		window.display();
	}
	return OPTION_EXIT;
}

#define PADDLE_WIDTH 20;
#define PADDLE_HEIGHT 100;

int play(sf::RenderWindow& window) {
	window.setMouseCursorVisible(false);

	sf::Vector2i windowCenter(windowWidth / 2, windowHeight / 2);

	extern int gameLevel;

	int ballSpeed = (gameLevel == LEVEL_EASY) ? 10 : 15;
	int ballRadius = 10;
	float ballInitDirection = 270;
	Ball ball(ballRadius, ballSpeed, ballInitDirection);
	ball.setPosition((float)windowCenter.x, (float)windowCenter.y);

	// Define paddle size
	int paddleWidth = 10;
	int paddleHeight = 100;
	int paddleMaxY = windowHeight - paddleHeight / 2;
	int paddleMinY = paddleHeight / 2;

	int userPaddleX = windowWidth - 50;
	Paddle userPaddle(paddleWidth, paddleHeight, userPaddleX, windowCenter.y);

	int compPaddleX = 50;
	Paddle compPaddle(paddleWidth, paddleHeight, compPaddleX, windowCenter.y);

	sf::Font mfont;
	mfont.loadFromFile("arial.ttf");
	Scoreboard scoreboard(mfont);
	scoreboard.setPosition(windowWidth*0.5, windowHeight*0.05);
	
	// 10-90 110-190 210-290 310-390 410-490 510-590 
	int lineLength = 60;
	int lineDistance = 40;
	int numberOfLines = windowHeight-200 / (lineLength + lineDistance);
	int yPos = 60;	// so that the first line starts at y=10 and there be a space at the top and bottom
	sf::VertexArray centerLine(sf::Lines, numberOfLines*2);
	for (int i = 0; i < 12; i++) {
		yPos += (i % 2 == 0) ? lineDistance : lineLength;
		centerLine[i].position = sf::Vector2f(windowCenter.x, yPos);
		centerLine[i].color = sf::Color::White;
	}

	sf::SoundBuffer buf;
	if (!buf.loadFromFile("sound.wav")) {
		printf("sound failure");
	}

	sf::Sound sound;
	sound.setBuffer(buf);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				exit(0);
			}
		}

		if (clock.getElapsedTime().asMilliseconds() > 13.f) {
			if (scoreboard.getScores()[USER] == MAX_SCORE || scoreboard.getScores()[COMPUTER] == MAX_SCORE) {
				char* endText = (scoreboard.getScores()[USER] == MAX_SCORE) ? "You Win!" : "You Lose!";
				return end(window, endText);
			}

			//ball.move();

			// Check if ball is in goal
			if (ball.isOutOfLeftBound() || ball.isOutOfRightBound(windowWidth)) {
				if (ball.isOutOfRightBound(windowWidth)) {
					scoreboard.incrementScore(COMPUTER);
				}
				else {
					scoreboard.incrementScore(USER);
				}
				ball.setPosition(windowCenter.x, windowCenter.y);
				ball.setDirection(ballInitDirection);

				userPaddle.setPosition(userPaddleX, windowCenter.y);
				compPaddle.setPosition(compPaddleX, windowCenter.y);
			}

			// Check collision with the walls or paddles
			if (ball.getBottomEdgeCoordinates().y >= windowHeight || ball.getTopEdgeCoordinates().y <= 0) {
				float ballDirection = (ball.getDirection() <= 180) ? 180 - ball.getDirection(): 
					540 - ball.getDirection();
				ball.setDirection(ballDirection);
				sound.play();
			}
			else if (ball.hasCollided(&userPaddle)) {
				float newDirection = (ball.getY() - userPaddle.getY())*-0.45 + 270;
				ball.setDirection(newDirection);
				sound.play();
			}
			else if (ball.hasCollided(&compPaddle)) {
				float newDirection = (ball.getY() - compPaddle.getY())*0.45 + 90;
				ball.setDirection(newDirection);
				sound.play();
			}

			// Move user paddle according to the cursor position
			int mouseY = sf::Mouse::getPosition().y;
			
			int userY = userPaddle.getY();
			if (mouseY != userY) {
				if (mouseY >= paddleMaxY) {
					userPaddle.setTargetY(paddleMaxY);
				}
				else if (mouseY <= paddleMinY) {
					userPaddle.setTargetY(paddleMinY);
				}
				else {
					userPaddle.setTargetY(mouseY);
				}
			}

			// Move AI paddle
			int compY = compPaddle.getY();
			int compPaddleSpeed = 10;
			float projectionDistance = (LEVEL_EASY) ? .4 : .5;
			if (ball.getX() <= windowWidth * projectionDistance) {
				float projectionY = -gameLevel * ball.getSpeed() * 10 * cos(ball.getDirection()*PI / 180) + ball.getY();
				if (abs(compY - projectionY) >= 50) {
					if (compY <= projectionY && compPaddle.getY() + 5 <= paddleMaxY) {
						compPaddle.addTargetY(compPaddleSpeed);
					}
					else if (compY >= projectionY && compY - 5 >= paddleMinY) {
						compPaddle.addTargetY(-compPaddleSpeed);
					}
				}
			}
			else {
				if (compY <= windowHeight * .45) {
					compPaddle.addTargetY(compPaddleSpeed);
				}
				else if (compY >= windowHeight * .55) {
					compPaddle.addTargetY(-compPaddleSpeed);
				}
				
			}


			userPaddle.move();
			compPaddle.move();
			ball.move();

			clock.restart();
		}

		window.clear();
		window.draw(centerLine);
		window.draw(ball.getImage());
		window.draw(userPaddle.getImage());
		window.draw(compPaddle.getImage());
		window.draw(scoreboard.getImage());
		window.display();
	}

	return OPTION_EXIT;
}
