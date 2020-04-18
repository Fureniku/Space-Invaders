#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/DisplayManager.h"
#include "../include/GameManager.h"
#include "../include/Alien.h"

//The main menu screen - shown when you first load the game.
void DisplayManager::drawMainMenuScreen(sf::RenderWindow &window, bool &inMainMenu, GameManager &gm) {
	window.clear();

	//Every 50 frames, switch the render texture for our aliens, to animate them.
	if (timer % 50 == 0) {
		m1.toggleType();
		a1.toggleType();
		a2.toggleType();
		a3.toggleType();
	}

	//Draw text based on the current frame number to give an animated feel to the main menu.
	drawText(window, xSize / 2, 30, "THE INVADERS", true, 24);
	if (timer > 60) drawText(window, 87, 70, "FROM", false, 36);
	if (timer > 100) drawText(window, 252, 70, "SPACE", false, 36);

	if (timer > 150) drawText(window, xSize / 2, 160, "SCORE GUIDE", true, 18);

	if (timer > 180) {
		drawText(window, xSize / 2 - 50, 200, "= 100 POINTS", false, 18);
		window.draw(m1.getSprite());
	}

	if (timer > 210) {
		drawText(window, xSize / 2 - 50, 240, "=  30 POINTS", false, 18);
		window.draw(a1.getSprite());
	}

	if (timer > 240) {
		drawText(window, xSize / 2 - 50, 280, "=  20 POINTS", false, 18);
		window.draw(a2.getSprite());
	}

	if (timer > 270) {
		drawText(window, xSize / 2 - 50, 320, "=  10 POINTS", false, 18);
		window.draw(a3.getSprite());
	}

	if (timer > 300) {
		//Flash every 50 frames
		if (timer % 100 < 50) {
			drawText(window, xSize / 2, ySize - 80, "PRESS [SPACE] TO START", true, 18);
		}
		//Change the text based on current mute status
		std::string mute = gm.playSound() ? "MUTE" : "UNMUTE";
		drawText(window, xSize / 2, ySize - 20, "PRESS [S] TO " + mute + " GAME", true, 12);
	}

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::S) {
				//Mute/unmute game when they press S.
				gm.toggleSound();
			}
			if (event.key.code == sf::Keyboard::Space) {
				if (timer < 300) {
					//If the screen loading in animation hasn't finished, skip it and show everything
					timer = 300;
				}
				else {
					//Otherwise, start the game!
					inMainMenu = false;
				}
			}
		}
	}
	window.display();
	timer++;

	if (timer > 100000) timer = 300; //Stop it from going out of bounds, as we don't do anything over 300 anyway
}

//The screen displayed when a user presses Escape
void DisplayManager::drawPauseScreen(sf::RenderWindow &window, GameManager &gm) {
	window.clear();

	drawText(window, xSize / 2, 100, "GAME PAUSED", true, 14);
	drawText(window, xSize / 2, 140, "PRESS [SPACE] OR [ENTER] TO RESUME", true, 14);
	std::string mute = gm.playSound() ? "MUTE" : "UNMUTE";
	drawText(window, xSize / 2, 200, "PRESS [S] TO " + mute + " GAME", true, 14);

	window.display();

	while (window.pollEvent(event)) {

		// User has pressed the close button
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		//Check for left/right/space press
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::S) {
				//Toggle sounds
				gm.toggleSound();
			}
			if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter) {
				//Unpause/resume the game
				gm.unpauseGame();
			}
		}
	}
}

//the screen displayed when a player loses
void DisplayManager::drawGameOverScreen(sf::RenderWindow &window, GameManager &gm) {
	window.clear();
	drawText(window, xSize / 2, 100, "GAME OVER!", true, 14);
	drawText(window, xSize / 2, 140, "PRESS [SPACE] TO START NEW GAME", true, 14);
	drawText(window, xSize / 2, 180, "PRESS [ESCAPE] TO EXIT", true, 14);
	window.display();

	while (window.pollEvent(event)) {
		// User has pressed the close button
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		//Check for left/right/space press
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				//Give up and close the game
				window.close();
			}
			if (event.key.code == sf::Keyboard::Space) {
				//Start a new game (from a losing position)
				gm.newGame(false);
			}
		}
	}
}

//Only call in other draw methods, as it doesn't handle clear/display.
//Create a text object and draw it
void DisplayManager::drawText(sf::RenderWindow &window, int posX, int posY, std::string str, bool centralize, int fontSize) {
	sf::Text text;

	text.setFont(font);
	text.setString(str);
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(fontSize);

	if (centralize) {
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(posX, posY);
	}
	else {
		//Offset down by 4, to align origin so 0,0 is top-left corner of string
		text.setPosition(posX, posY + 4);
	}

	window.draw(text);
}

