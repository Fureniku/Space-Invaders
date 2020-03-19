#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

sf::RectangleShape Player::getRenderer() {
	return render;
}

void Player::moveLeft(sf::RectangleShape &shape) {
	shape.move(-15, 0);
}

void Player::moveRight(sf::RectangleShape &shape) {
	shape.move(15, 0);
}

void Player::shoot() {
}