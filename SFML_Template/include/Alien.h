#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

class GameManager;

class Alien {
protected:
	sf::Texture texture_a;
	sf::Texture texture_b;
	sf::Sprite sprite;
	bool aType = true;
	bool dead = false;
	int value = 0;
	std::string texName;

public:
	Alien(sf::Color col, int startX, int startY, std::string textureName, int pointsValue) {
		texName = textureName;
		value = pointsValue;
		//For initial creation, use a type texture
		if (texture_a.loadFromFile(".\\assets\\textures\\" + textureName + "a.png")) {
			sprite.setTexture(texture_a);
			sprite.setOrigin(texture_a.getSize().x / 2.0F, texture_a.getSize().y / 2.0F);
			sprite.setPosition(startX, startY);
			sprite.setColor(col);
		}
		//Register the B texture as well, for later use in animation
		texture_b.loadFromFile(".\\assets\\textures\\" + textureName + "b.png");
	}

	sf::Sprite getSprite();
	sf::Sprite move(bool moveRight, int moveX, int moveY);
	void setRenderer(sf::Sprite shape);
	bool getType();
	void kill(GameManager &manager);
	bool isDead();
	void toggleType();
	int getPointValue();
	void shoot(int chance, std::vector<Bullet> &bulletVector);
};