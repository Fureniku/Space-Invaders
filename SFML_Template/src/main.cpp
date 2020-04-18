#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Alien.h"
#include "../include/GameManager.h"
#include "../include/DisplayManager.h"

//Create object of font for drawing text
sf::Font font;

//Are we still on the title screen?
bool inMainMenu = true;

//The size of our screen. Some things will dynamically resize, but not everything. Don't change this without considering the consequences.
int screenSizeX = 512;
int screenSizeY = 512;

int main() {
	//Create our game window
	sf::RenderWindow window(sf::VideoMode(screenSizeX, screenSizeY), "The Invaders from Space", sf::Style::Default);

	//Place the game window in the middle of the screen (screen width/2 - window size/2, same for height)
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width / 2) - (screenSizeX / 2), (sf::VideoMode::getDesktopMode().height / 2) - (screenSizeY / 2)));
	window.setFramerateLimit(60); // Set the limit of the the number of frames per second. Changing this will impact some game mechanics.

	//Create an object of our player to use
	Player player(screenSizeX, screenSizeY);

	//Create objects of game manager and display manager
	GameManager gameManager(player, screenSizeX, screenSizeY);
	DisplayManager displayManager(screenSizeX, screenSizeY);

	//Set up a new game, from a losers perspective (we've just opened it, so we certainly didn't win!)
	gameManager.setupGame(false);

	//Run until the user closes the window
	while (window.isOpen()) {
		if (inMainMenu) {
			//Draw the main menu screen
			displayManager.drawMainMenuScreen(window, inMainMenu, gameManager);
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
				gameManager.eventHandler(window);
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