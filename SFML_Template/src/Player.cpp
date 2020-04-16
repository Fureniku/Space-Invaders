#include "../include/Player.h"
#include "../include/GameManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

void Player::drawLives(sf::RenderWindow &window) {
	for (int i = 0; i < lives-1; i++) {
		sf::Sprite s = sprite;

		s.setOrigin(texture.getSize().x / 2.0F, texture.getSize().y / 2.0F);
		s.setPosition((40 + i * (texture.getSize().x + 5)), ySize - 20);
		s.setColor(sf::Color(0, 255, 0));

		window.draw(s);
	}
}

void Player::shoot(GameManager &manager) {
	if (!bulletActive) {
		manager.addBulletToVector(Bullet(true, sprite.getPosition().x, sprite.getPosition().y + 4));
		bulletActive = true;
	}
}

void Player::getShot() {
	if (lives > 0 && respawnTimer <= 0) {
		lives--;
		respawnTimer = respawnTime;
	}
}

bool Player::isPlayerDead() {
	if (respawnTimer > 0) {
		std::cout << "Respawn timer: " << respawnTimer << std::endl;
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

void Player::addLives(int amt) {
	lives += amt;
}

void Player::resetPosition() {
	respawnTimer = 0; //Ensure timer is zero on reset - useful for after a new game etc
	sprite.setPosition(defaultX, defaultY);
}

sf::Sprite Player::getSprite() {
	if (isPlayerDead()) {
		sprite.setTexture(texture_dead);
	}
	else {
		sprite.setTexture(texture);
	}
	return sprite;
}

void Player::move(int amount) {
	if (respawnTimer <= 0) {
		sprite.move(amount, 0);
	}
}