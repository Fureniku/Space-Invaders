#include "../include/Player.h"
#include "../include/GameManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

//Draw the player's lives on-screen, in the bottom-left corner.
void Player::drawLives(sf::RenderWindow &window) {
	for (int i = 0; i < lives-1; i++) {
		sf::Sprite s = sprite;

		s.setOrigin(texture.getSize().x / 2.0F, texture.getSize().y / 2.0F);
		s.setPosition((40 + i * (texture.getSize().x + 5)), ySize - 20);
		s.setColor(sf::Color(0, 255, 0));

		window.draw(s);
	}
}

//Called when the player presses space
void Player::shoot(GameManager &manager) {
	if (!bulletActive) {
		if (manager.playSound()) {
			sfx_shoot.play();
		}
		manager.addBulletToVector(Bullet(true, sprite.getPosition().x, sprite.getPosition().y + 4));
		bulletActive = true;
	}
}

//Called when a player is shot by an alien.
void Player::getShot(GameManager &manager) {
	if (lives > 0 && respawnTimer <= 0) {
		if (manager.playSound()) {
			sfx_die.play();
		}
		lives--;
		respawnTimer = respawnTime;
	}
}

//Checks if the player is dead - used to validate bullet collisions etc
bool Player::isPlayerDead() {
	if (respawnTimer > 0) {
		respawnTimer--;
		//Respawn timer reaches zero - move them to spawn point
		if (respawnTimer == 0) {
			resetPosition();
		}
		return true;
	}
	return false;
}

int Player::getLives() {
	return lives;
}

//Increas the player lives by the amount specified. Increase by 1 for a victory, increase by 3 for a defeat (to reset)
void Player::addLives(int amt) {
	lives += amt;
}

//Move the player back to starting position and so on.
void Player::resetPosition() {
	respawnTimer = 0; //Ensure timer is zero on reset - useful for after a new game etc
	bulletActive = false;
	sprite.setPosition(defaultX, defaultY);
}

//Get the player's texture for rendering
sf::Sprite Player::getSprite() {
	if (isPlayerDead()) {
		sprite.setTexture(texture_dead);
	}
	else {
		sprite.setTexture(texture);
	}
	return sprite;
}

//Move the player, so long as they are alive.
void Player::move(int amount) {
	if (respawnTimer <= 0) {
		sprite.move(amount, 0);
	}
}