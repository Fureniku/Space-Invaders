#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Alien {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	bool aType = true;
	std::string texName;

	Alien(sf::Color col, int startX, int startY, std::string textureName, float scale) {
		texName = textureName;
		//For initial creation, use a type texture
		if (texture.loadFromFile(".\\assets\\textures\\" + textureName + "a.png")) {
			sprite.setTexture(texture);
			sprite.setScale(sf::Vector2f(scale, scale));
			sprite.setOrigin(texture.getSize().x / 2.0F, texture.getSize().y / 2.0F);
			sprite.setPosition(startX, startY);
			sprite.setColor(col);
		}
	}

	sf::Sprite getRenderer();
	void move(sf::Sprite &shape, bool moveRight, int moveX, int moveY);
	void setRenderer(sf::Sprite shape);
	bool getType();
	void toggleType();
};