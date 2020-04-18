#include "../include/Bullet.h"

sf::RectangleShape Bullet::getSprite() {
	return render;
}

void Bullet::setSprite(sf::RectangleShape shape) {
	render = shape;
}

//Move the bullet by the amount. Called from GameManager, which passes the properties for speed and direction based on the bullet owner.
void Bullet::move(sf::RectangleShape &shape, int amount) {
	shape.move(0, amount);
}

