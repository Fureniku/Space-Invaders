#include "../include/Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

sf::Sprite Player::getRenderer() {
	return sprite;
}

void Player::move(sf::Sprite &shape, int amount) {
	shape.move(amount, 0);
}

void Player::shoot() {
}