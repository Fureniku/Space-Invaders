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

	//Switch between A texture and B texture every time the alien moves
	this->toggleType();

	return sprite;
}

//Check which current texture type we're using
bool Alien::getType() {
	return aType;
}

//Switch indiscriminately between A and B 
void Alien::toggleType() {
	aType = !aType;
}

//Called when the player shoots an alien. Adds score, plays sound if appropriate and sets the alien to dead.
void Alien::kill(GameManager &manager) {
	manager.addToScore(getPointValue());
	if (manager.playSound()) {
		sfx_dead.setBuffer(buffer_dead);
		sfx_dead.play();
	}
	dead = true;
}

//Checks if the alien is dead. Used a lot to ensure it can't be shot, won't render etc when dead.
bool Alien::isDead() {
	return dead;
}

//How much score does this alien give whne killed
int Alien::getPointValue() {
	return value;
}

//Attempt to fire a shot. If the random number generator returns one, fire a shot.
void Alien::shoot(int chance, std::vector<Bullet> &bulletVector) {
	if (rand() % chance == 1) {
		bulletVector.push_back(Bullet(false, getSprite().getPosition().x, getSprite().getPosition().y));
	}
}