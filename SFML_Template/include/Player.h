#pragma once
#include <SFML/Graphics.hpp>
#include "Properties.h"
#include "Bullet.h"

class Player {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	Properties p;

	Player() {
		if (texture.loadFromFile(".\\assets\\textures\\Player.png")) {
			sprite.setTexture(texture);

			//sprite.setSize(sf::Vector2f(26.0F * p.getScale(), 16.0F * p.getScale()));
			sprite.setOrigin(texture.getSize().x / 2.0F, texture.getSize().y / 2.0F);
			sprite.setPosition(p.getWindowXSize() / 2, p.getWindowYSize() - (30 * p.getScale()));
			sprite.setColor(sf::Color(0, 255, 0));
		}
	}

	sf::Sprite getRenderer();
	void shoot();
	void move(sf::Sprite &shape, int amount);
};