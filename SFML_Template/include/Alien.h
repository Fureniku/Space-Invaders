#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>
#include <iostream>

class GameManager;

class Alien {
private:
	//Create objects to hold our two textures for each state of the animation
	sf::Texture texture_a;
	sf::Texture texture_b;
	//Which stage of the animation we are in
	bool aType = true;
	bool dead = false;
	//The amount of points awarded for killing the alien
	int value = 0;
	//The name of the texture passed via the constructor
	std::string texName;
protected:
	//Object of the sprite so we're not constantly making a new one every frame
	sf::Sprite sprite;

	//SFX things
	sf::SoundBuffer buffer_dead;
	sf::Sound sfx_dead;
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

		buffer_dead.loadFromFile(".\\assets\\sounds\\invaderkilled.wav");
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