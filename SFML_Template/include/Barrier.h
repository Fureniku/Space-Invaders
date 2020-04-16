#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Barrier {
private:
	int health = 4;
	sf::Texture texture_100;
	sf::Texture texture_75;
	sf::Texture texture_50;
	sf::Texture texture_25;
	sf::Sprite sprite;
	std::string texName;

public:
	Barrier(int posX, int posY, std::string textureName, int rotation) {
		texName = textureName;
		if (texture_100.loadFromFile(".\\assets\\textures\\" + textureName + "_100.png")) {
			sprite.setTexture(texture_100);
			sprite.setOrigin(texture_100.getSize().x / 2.0F, texture_100.getSize().y / 2.0F);
			sprite.setPosition(posX, posY);
			sprite.setRotation(rotation);

			//Unless someone messed with our files, these will all be here if _100 was.
			texture_75.loadFromFile(".\\assets\\textures\\" + textureName + "_75.png");
			texture_50.loadFromFile(".\\assets\\textures\\" + textureName + "_50.png");
			texture_25.loadFromFile(".\\assets\\textures\\" + textureName + "_25.png");
		}
		
	}

	bool getShot(); //Return true when it blocks a bullet, false otherwise.
	sf::Sprite getSprite();
	void updateSprite();
	int getHealth();
};