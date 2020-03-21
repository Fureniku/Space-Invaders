#include "../include/Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

sf::RectangleShape Player::getRenderer() {
	return render;
}

void Player::move(sf::RectangleShape &shape, int amount) {
	shape.move(amount, 0);
}

void Player::shoot() {
}