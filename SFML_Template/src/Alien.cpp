#include "../include/Alien.h"
#include "../include/GameManager.h"
#include <iostream>

sf::Sprite Alien::getSprite() {
	//Assign the texture depending on which stage of animation we're in
	if (aType) {
		sprite.setTexture(texture_a);
	}
	else {
		sprite.setTexture(texture_b);
	}
	//Return the sprite with the updated texture
	return sprite;
}

void Alien::setRenderer(sf::Sprite s) {
	sprite = s;
}

sf::Sprite Alien::move(bool moveRight, int moveX, int moveY) {
	if (moveY > 0) {
		sprite.move(0, moveY);
	}
	else {
		sprite.move(moveRight ? moveX : -moveX, 0);
	}

	//Switch between A texture and B texture
	this->toggleType();

	return sprite;
}

bool Alien::getType() {
	return aType;
}

void Alien::toggleType() {
	aType = !aType;
}

void Alien::kill(GameManager &manager) {
	manager.addToScore(getPointValue());
	dead = true;
}

bool Alien::isDead() {
	return dead;
}

int Alien::getPointValue() {
	return value;
}

void Alien::shoot(int chance, std::vector<Bullet> &bulletVector) {
	if (rand() % chance == 1) {
		bulletVector.push_back(Bullet(false, getSprite().getPosition().x, getSprite().getPosition().y));
	}
}