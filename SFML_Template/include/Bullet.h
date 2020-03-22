#pragma once
#include <SFML/Graphics.hpp>
#include "Properties.h"

class Bullet {
public:
	sf::RectangleShape render;
	bool isPlayerOwned;

	Bullet() {}

	Bullet(bool playerOwned, int startX, int startY, float scale) {
		render.setSize(sf::Vector2f(2.0F*scale, 10.0F*scale));
		render.setOrigin(render.getSize().x / 2.0F, render.getSize().y / 2.0F);
		render.setPosition(startX, startY);
		render.setFillColor(sf::Color::White);

		isPlayerOwned = playerOwned;
	}

	sf::RectangleShape getRenderer();
	void setRenderer(sf::RectangleShape shape);
	void move(sf::RectangleShape &shape, int amount);
};