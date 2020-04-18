#pragma once
#include "Alien.h"
#include <string>

class Mothership : public Alien {
private:
	sf::SoundBuffer buffer_move;
	sf::Sound sfx_move;
	bool isSfxPlaying = false;
public:
	//Default constructor for when it doesn't actually exist
	//Pass default values to parent class Alien.
	Mothership() : Alien(sf::Color::Red, 0, 0, "Mothership_", 100) {}

	Mothership(int startX, int startY) : Alien(sf::Color::Red, startX, startY, "Mothership_", 100) {
		buffer_move.loadFromFile(".\\assets\\sounds\\ufo_highpitch.wav");
		sfx_move.setLoop(true);
		sfx_move.setVolume(25); //"That mothership sound is amazing, lets have it at full volume!" said no one ever.
	}

	void move();
	void toggleSFX(bool play);
};
