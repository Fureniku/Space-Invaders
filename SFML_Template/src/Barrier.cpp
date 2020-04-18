#include "../include/Barrier.h"

//Process a bullets collision with a barrier. Bool is for whether a bullet should be removed - if the barrier had health, it blocked the bullet and returns true.
bool Barrier::getShot() {
	if (health <= 0) {
		return false;
	}
	health -= 1;
	return true;
}

//Return the sprite based on the barriers health
sf::Sprite Barrier::getSprite() {
	if (health == 4) { sprite.setTexture(texture_100); }
	if (health == 3) { sprite.setTexture(texture_75); }
	if (health == 2) { sprite.setTexture(texture_50); }
	if (health == 1) { sprite.setTexture(texture_25); }
	return sprite;
}

//Return the barriers current health
int Barrier::getHealth() {
	return health;
}