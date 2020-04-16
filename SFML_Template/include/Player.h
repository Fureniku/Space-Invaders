#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"

class GameManager;

class Player {
private:
	sf::Texture texture;
	sf::Texture texture_dead;
	sf::Sprite sprite;

	//How many lives the player has
	int lives = 3;

	int defaultX = 0;
	int defaultY = 0;

	int xSize;
	int ySize;

	int respawnTimer = 0;
	int respawnTime = 150; //How many frames it takes to respawn

public:
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
	}
	
	void drawLives(sf::RenderWindow &window);
	void shoot(GameManager &manager);

	sf::Sprite getSprite();
	void move(int amount);

	void getShot();
	int getLives();
	void addLives(int amt);
	void resetPosition();

	bool isPlayerDead();
};