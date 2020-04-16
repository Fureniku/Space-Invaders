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
		s.setPosition((40 + i * (texture.getSize().x + 5)), p.getWindowYSize() - 20);
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
	if (lives > 0) {
		lives--;

		cout << lives << endl;

		resetPosition();
	}
}

int Player::getLives() {
	return lives;
}

void Player::addLives(int amt) {
	lives += amt;
}

void Player::resetPosition() {
	sprite.setPosition(defaultX, defaultY);
}

sf::Sprite Player::getSprite() {
	return sprite;
}

void Player::move(int amount) {
	sprite.move(amount, 0);
}