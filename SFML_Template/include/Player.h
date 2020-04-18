#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"

class GameManager;

class Player {
private:
	sf::Texture texture;
	sf::Texture texture_dead;
	sf::Sprite sprite;

	sf::SoundBuffer buffer_shoot;
	sf::SoundBuffer buffer_die;
	sf::Sound sfx_shoot;
	sf::Sound sfx_die;

	//How many lives the player has
	int lives = 3;

	//The spawn position in the middle of the screen, used to reset the player on death.
	int defaultX = 0;
	int defaultY = 0;

	//Screen size, used for positioning the player
	int xSize;
	int ySize;

	int respawnTimer = 0; //Set to respawnTime and then decreased by 1 per frame when the player dies.
	int respawnTime = 150; //How many frames it takes to respawn

public:
	//Set to true when the player fires a shot, and back to false when the bullet is removed.
	bool bulletActive = false;

	Player(int screenSizeX, int screenSizeY) {
		xSize = screenSizeX;
		ySize = screenSizeY;
		if (texture.loadFromFile(".\\assets\\textures\\Player.png")) {
			sprite.setTexture(texture);

			sprite.setOrigin(texture.getSize().x / 2.0F, texture.getSize().y / 2.0F);
			sprite.setPosition(xSize / 2, ySize - 44);

			defaultX = xSize / 2;
			defaultY = ySize - 44;

			sprite.setColor(sf::Color(0, 255, 0));
			texture_dead.loadFromFile(".\\assets\\textures\\Player_Dead.png");
		}

		if (buffer_shoot.loadFromFile(".\\assets\\sounds\\shoot.wav")) {
			sfx_shoot.setBuffer(buffer_shoot);
		}
		if (buffer_die.loadFromFile(".\\assets\\sounds\\explosion.wav")) {
			sfx_die.setBuffer(buffer_die);
		}
	}
	
	void drawLives(sf::RenderWindow &window);
	void shoot(GameManager &manager);

	sf::Sprite getSprite();
	void move(int amount);

	void getShot(GameManager &manager);
	int getLives();
	void addLives(int amt);
	void resetPosition();

	bool isPlayerDead();
};