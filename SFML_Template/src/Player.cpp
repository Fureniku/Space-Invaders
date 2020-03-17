#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

sf::RectangleShape Player::getRenderer() {
	return render;
}

void Player::moveLeft(sf::RectangleShape &shape) {
	shape.move(-10, 0);
	cout << "slide to the left" << endl;
}

void Player::moveRight(sf::RectangleShape &shape) {
	shape.move(10, 0);
	cout << "slide to the right" << endl;
}

void Player::shoot() {
	cout << "criss cross" << endl;
}