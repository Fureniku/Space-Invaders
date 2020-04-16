#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Alien.h"
#include "../include/GameManager.h"
#include "../include/DisplayManager.h"

//Create object of font for drawing text
sf::Font font;

bool inMainMenu = true;

int screenSizeX = 512;
int screenSizeY = 512;

int main() {
	sf::RenderWindow window(sf::VideoMode(screenSizeX, screenSizeY), "The Invaders from Space", sf::Style::Default);

	//Place the game window in the middle of the screen (screen width/2 - window size/2, same for height)
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width / 2) - (screenSizeX / 2), (sf::VideoMode::getDesktopMode().height / 2) - (screenSizeY / 2)));
	window.setFramerateLimit(60); // Set the limit of the the number of frames per second

	Player player(screenSizeX, screenSizeY);

	GameManager gameManager(player, screenSizeX, screenSizeY);
	DisplayManager displayManager(screenSizeX, screenSizeY);

	gameManager.setupGame(false);

	//Run until the user closes the window
	while (window.isOpen()) {
		if (inMainMenu) {
			//Draw the main menu screen
			displayManager.drawMainMenuScreen(window, inMainMenu);
		}
		else {
			if (gameManager.gameOver()) {
				//Draw the game over screen
				displayManager.drawGameOverScreen(window, gameManager);
			} else if (gameManager.gamePaused()) {
				//Draw the pause screen
				displayManager.drawPauseScreen(window, gameManager);
			} else {
				//Run the game
				gameManager.keyListener(window);
				gameManager.gameTick();

				window.clear();
				//Draw the game screen
				gameManager.drawGameObjects(window);
				window.display();
			}
		}
	}

	return 0;
}