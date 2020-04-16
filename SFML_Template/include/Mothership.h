#pragma once
#include "Alien.h"
#include <string>

class Mothership : public Alien {
public:
	//Default constructor for when it doesn't actually exist
	Mothership() : Alien(sf::Color::Red, 0, 0, "Mothership_", 100) {}

	Mothership(int startX, int startY) : Alien(sf::Color::Red, startX, startY, "Mothership_", 100) {}

	void move();
};
