#include "Alien.h"
#include <iostream>

sf::RectangleShape Alien::getRenderer() {
	return render;
}

void Alien::setDead() {
	dead = true;
	std::cout << "splat" << std::endl;
}

bool Alien::isDead() {
	return dead;
}

void Alien::setRenderer(sf::RectangleShape shape) {
	render = shape;
}

void Alien::move(sf::RectangleShape shape, int moveX, int moveY) {
	std::cout << "Move alien. current pos: " << shape.getPosition().x << " moving by " << moveX << std::endl;
	shape.move(moveX, moveY);
}
