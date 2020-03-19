#include "Alien.h"
#include <iostream>

sf::RectangleShape Alien::getRenderer() {
	return render;
}

void Alien::setDead() {
	dead = true;
}

bool Alien::isDead() {
	return dead;
}

void Alien::setRenderer(sf::RectangleShape shape) {
	render = shape;
}

void Alien::move(sf::RectangleShape shape, int moveX, int moveY) {
	shape.move(moveX, moveY);
}
