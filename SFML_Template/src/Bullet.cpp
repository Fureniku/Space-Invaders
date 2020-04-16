#include "../include/Bullet.h"

sf::RectangleShape Bullet::getSprite() {
	return render;
}

void Bullet::setSprite(sf::RectangleShape shape) {
	render = shape;
}

void Bullet::move(sf::RectangleShape &shape, int amount) {
	if (isPlayerOwned) {
		shape.move(0, -15);
	}
	else {
		shape.move(0, 10);
	}
}

