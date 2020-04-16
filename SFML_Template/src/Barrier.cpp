#include "../include/Barrier.h"

bool Barrier::getShot() {
	if (health <= 0) {
		return false;
	}
	health -= 1;
	updateSprite();
	return true;
}

void Barrier::updateSprite() {
	if (health == 4) { sprite.setTexture(texture_100); }
	if (health == 3) { sprite.setTexture(texture_75); }
	if (health == 2) { sprite.setTexture(texture_50); }
	if (health == 1) { sprite.setTexture(texture_25); }
}

sf::Sprite Barrier::getSprite() {
	if (health == 4) { sprite.setTexture(texture_100); }
	if (health == 3) { sprite.setTexture(texture_75); }
	if (health == 2) { sprite.setTexture(texture_50); }
	if (health == 1) { sprite.setTexture(texture_25); }
	return sprite;
}

int Barrier::getHealth() {
	return health;
}