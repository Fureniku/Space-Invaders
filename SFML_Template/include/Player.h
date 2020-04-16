#pragma once
#include <SFML/Graphics.hpp>
#include "Properties.h"
#include "Bullet.h"

class GameManager;

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	Properties p;

	//How many lives the player has
	int lives = 3;

	int defaultX = 0;
	int defaultY = 0;

public:
	bool bulletActive = false;

	Player() {
		if (texture.loadFromFile(".\\assets\\textures\\Player.png")) {
			sprite.setTexture(texture);

			sprite.setOrigin(texture.getSize().x / 2.0F, texture.getSize().y / 2.0F);
			sprite.setPosition(p.getWindowXSize() / 2, p.getWindowYSize() - 44);

			defaultX = p.getWindowXSize() / 2;
			defaultY = p.getWindowYSize() - 44;

			sprite.setColor(sf::Color(0, 255, 0));
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
};