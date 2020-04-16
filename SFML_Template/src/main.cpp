#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Properties.h"
#include "../include/Alien.h"
#include "../include/GameManager.h"
#include "../include/DisplayManager.h"

//Create object of font for drawing text
sf::Font font;

Properties prop;

bool inMainMenu = true;

int main() {
	sf::RenderWindow window(sf::VideoMode(prop.getWindowXSize(), prop.getWindowYSize()), "The Invaders from Space", sf::Style::Default);

	//Place the game window in the middle of the screen (screen width/2 - window size/2, same for height)
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width / 2) - (prop.getWindowXSize() / 2), (sf::VideoMode::getDesktopMode().height / 2) - (prop.getWindowYSize() / 2)));
	window.setFramerateLimit(60); // Set the limit of the the number of frames per second

	Player player;

	GameManager gameManager(player);
	DisplayManager displayManager;

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