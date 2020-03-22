#include "../include/Alien.h"
#include <iostream>

sf::Sprite Alien::getRenderer() {
	//Get the texture name when creating the alien, and check whether to render type A or type B (inverted every time they move)
	if (texture.loadFromFile(".\\assets\\textures\\" + texName + (aType ? "a" : "b") + ".png")) {
		sprite.setTexture(texture);
	}
	return sprite;
}

void Alien::setRenderer(sf::Sprite s) {
	sprite = s;
}

void Alien::move(sf::Sprite &s, bool moveRight, int moveX, int moveY) {
	if (moveY > 0) {
		s.move(0, moveY);
	}
	else {
		s.move(moveRight ? moveX : -moveX, 0);
	}
}

bool Alien::getType() {
	return aType;
}

void Alien::toggleType() {
	aType = !aType;
}
