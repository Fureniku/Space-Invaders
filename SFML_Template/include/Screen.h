#include <SFML/Graphics.hpp>
#pragma once

class Screen {
public:
	int xSize = 224;
	int ySize = 256;
	sf::RenderWindow window(sf::VideoMode(xSize, ySize), "Spacey Bois", sf::Style::Default);

	Screen() {
		window = sf::RenderWindow window(sf::VideoMode(xSize, ySize), "Spacey Bois", sf::Style::Default);
	}
};