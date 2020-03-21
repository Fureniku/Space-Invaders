#include "../include/Alien.h"
#include <iostream>

sf::Sprite Alien::getRenderer() {
	if (texture.loadFromFile(".\\assets\\textures\\" + texName + (aType ? "a" : "b") + ".png")) {
		sprite.setTexture(texture);
	}
	return sprite;
}

void Alien::setRenderer(sf::Sprite s) {
	sprite = s;
}

void Alien::move(sf::Sprite s, int moveX, int moveY) {
	s.move(moveX, moveY);
}

bool Alien::getType() {
	return aType;
}

void Alien::toggleType() {
	aType = !aType;
}
