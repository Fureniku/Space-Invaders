#pragma once
#include <SFML/Graphics.hpp>
#include "Properties.h"

class Bullet {
public:
	sf::RectangleShape render;
	bool isPlayerOwned;

	Bullet() {}

	Bullet(bool playerOwned, int startX, int startY) {
		render.setSize(sf::Vector2f(2.0F, 10.0F));
		render.setOrigin(render.getSize().x / 2.0F, render.getSize().y / 2.0F);
		render.setPosition(startX, startY);
		render.setFillColor(sf::Color::White);

		isPlayerOwned = playerOwned;
	}

	sf::RectangleShape getSprite(); //Technically not a sprite but oh well
	void setSprite(sf::RectangleShape shape);
	void move(sf::RectangleShape &shape, int amount);
};