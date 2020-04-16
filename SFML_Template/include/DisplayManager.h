#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Alien.h"
#include "../include/Mothership.h"

class GameManager;

class DisplayManager {
private:
	//Create object of font for drawing text
	sf::Font font;

	sf::Event event;

	int xSize;
	int ySize;

	//The aliens we draw in the main menu
	Alien a1;
	Alien a2;
	Alien a3;

	Mothership m1;

	//Counter which increments every frame, used to animate the main menu
	int timer = 0;

public:
	DisplayManager(int screenSizeX, int screenSizeY) :
	a1(sf::Color::Magenta, screenSizeX / 2 - 70, 250, "Alien_1_", 0),
	a2(sf::Color::Yellow, screenSizeX / 2 - 70, 290, "Alien_2_", 0),
	a3(sf::Color::Cyan, screenSizeX / 2 - 70, 330, "Alien_3_", 0),

	m1(screenSizeX / 2 - 70, 210)
	{
		xSize = screenSizeX;
		ySize = screenSizeY;
		//Pixeled font by OmegaPC777 - https://www.dafont.com/pixeled.font
		if (!font.loadFromFile(".\\assets\\fonts\\pixeled.ttf")) {
			std::cout << "Font failed to load!" << std::endl;
		}
	}

	void drawMainMenuScreen(sf::RenderWindow &window, bool &inMainMenu);
	void drawPauseScreen(sf::RenderWindow &window, GameManager &gm);
	void drawGameOverScreen(sf::RenderWindow &window, GameManager &gm);

	void drawText(sf::RenderWindow &window, int posX, int posY, std::string str, bool centralize, int fontSize);
};